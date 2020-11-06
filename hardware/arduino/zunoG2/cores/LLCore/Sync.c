#include "Arduino.h"
#include "CrtxGcc.h"
#include "Threading.h"
#include "Sync.h"

ZunoSync_t gSyncUSART0 = ZUNO_SYNC_INIT_DEFAULT;
ZunoSync_t gSyncUSART1 = ZUNO_SYNC_INIT_DEFAULT;
ZunoSync_t gSyncUSART2 = ZUNO_SYNC_INIT_DEFAULT;
ZunoSync_t gSyncTIMER0 = ZUNO_SYNC_INIT_DEFAULT;
ZunoSync_t gSyncTIMER1 = ZUNO_SYNC_INIT_DEFAULT;
ZunoSync_t gSyncWTIMER0 = ZUNO_SYNC_INIT_DEFAULT;

typedef enum							SyncMode_e
{
	SyncModeWrite = 1,
	SyncModeRead
}										SyncMode_t;

#define ZUNO_SYNC_NO_TYPE			0x0
#define ZUNO_SYNC_FALSE				0x1
#define ZUNO_SYNC_TRUE				0x2

#define ZUNO_SYNC_SPIN_COUNT		0xA

static void _sectionEnter(volatile uint8_t *lp) {
	uint8_t			bLock;

	bLock = 0;
	do {
		while (__LDREXB(lp) != 0)// Wait until
			__NOP();
		bLock = __STREXB(1, lp);// Try to set
	} while (bLock !=0);//retry until lock successfully
	__DMB();// Do not start any other memory access until memory barrier is completed
}

static void _sectionLeave(volatile uint8_t *lp) {
	__DMB();// Ensure memory operations completed before
	lp[0] = 0;// releasing lock
}

SyncMaster_t zunoSyncOpen(ZunoSync_t *lpLock, SyncMaster_t value) {
	SyncMaster_t		master;

	_sectionEnter(&lpLock->bLock);
	if ((master = lpLock->master) == SyncMasterFree) {
		lpLock->master = value;
		master = value;
	}
	_sectionLeave(&lpLock->bLock);
	return (master);
}

void zunoSyncClose(ZunoSync_t *lpLock, SyncMaster_t value) {
	SyncMaster_t		master;

	_sectionEnter(&lpLock->bLock);
	if (lpLock->master == value)
		lpLock->master = SyncMasterFree;
	_sectionLeave(&lpLock->bLock);
}

static size_t _wait(ZunoSync_t *lpLock, SyncMaster_t value, SyncMode_t mode) {
	volatile uint16_t		counter;

	_sectionEnter(&lpLock->bLock);
	if (lpLock->master != value) {
		_sectionLeave(&lpLock->bLock);
		return (ZUNO_SYNC_NO_TYPE);
	}
	counter = lpLock->counter;
	if (mode == SyncModeWrite) {
		if (counter == 0) {
			lpLock->counter = ((uint16_t)-1);
			_sectionLeave(&lpLock->bLock);
			return (ZUNO_SYNC_TRUE);
		}
	} else if (counter != ((uint16_t)-1)) {
		lpLock->counter++;
		_sectionLeave(&lpLock->bLock);
		return (ZUNO_SYNC_TRUE);
	}
	_sectionLeave(&lpLock->bLock);
	return (ZUNO_SYNC_FALSE);
}

static ZunoError_t _lock(ZunoSync_t *lpLock, SyncMaster_t value, SyncMode_t mode) {
	size_t				out;
	size_t				i;
	void				*handle;

	while (0xFF) {
		i = 0;
		while (i++ < ZUNO_SYNC_SPIN_COUNT) {
			if ((out = _wait(lpLock, value, mode)) == ZUNO_SYNC_NO_TYPE)
				return (ZunoErrorSyncInvalidType);
			if (out == ZUNO_SYNC_TRUE)
				return (ZunoErrorOk);
		}
		handle = zunoGetCurrentThreadHandle();
		lpLock->handle = handle;
		zunoSuspendThread(handle);
	}
}

ZunoError_t zunoSyncLockRead(ZunoSync_t *lpLock, SyncMaster_t value) {
	return (_lock(lpLock, value, SyncModeRead));
}

ZunoError_t zunoSyncLockWrite(ZunoSync_t *lpLock, SyncMaster_t value) {
	return (_lock(lpLock, value, SyncModeWrite));
}

static void _relese(ZunoSync_t *lpLock, SyncMaster_t value) {
	size_t				counter;
	volatile void		*handle;

	_sectionEnter(&lpLock->bLock);
	if (lpLock->master == value) {
		if ((counter = lpLock->counter) == ((uint16_t)-1)) {
			lpLock->counter = 0;
			counter = 0;
		}
		else
			counter = --lpLock->counter;
		if ((handle = lpLock->handle) != 0) {
			zunoResumeThread((void *)handle);
			lpLock->handle = 0;
		}
	}
	_sectionLeave(&lpLock->bLock);
}

void zunoSyncReleseRead(ZunoSync_t *lpLock, SyncMaster_t value) {
	_relese(lpLock, value);
}

void zunoSyncReleseWrite(ZunoSync_t *lpLock, SyncMaster_t value) {
	_relese(lpLock, value);
}