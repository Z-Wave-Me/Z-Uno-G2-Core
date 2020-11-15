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
ZunoSync_t gSyncIC0 = ZUNO_SYNC_INIT_DEFAULT;
ZunoSync_t gSyncIC1 = ZUNO_SYNC_INIT_DEFAULT;

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

static size_t _wait(ZunoSync_t *lpLock, SyncMaster_t value, SyncMode_t mode, volatile uint8_t *lpKey) {
	volatile uint16_t		counter;

	_sectionEnter(&lpLock->bLock);
	if (lpLock->master != value || lpKey[0] == false) {
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

static ZunoError_t _lock(ZunoSync_t *lpLock, SyncMaster_t value, SyncMode_t mode, volatile uint8_t *lpKey) {
	size_t				bIo;
	size_t				out;
	size_t				i;
	void				*handle;

	bIo = zunoIsIOThread();
	while (0xFF) {
		i = 0;
		while (i++ < ZUNO_SYNC_SPIN_COUNT) {
			if ((out = _wait(lpLock, value, mode, lpKey)) == ZUNO_SYNC_NO_TYPE)
				return (ZunoErrorSyncInvalidType);
			if (out == ZUNO_SYNC_TRUE)
				return (ZunoErrorOk);
		}
		if (bIo == true)
			return (ZunoErrorTredIo);
		delay(1);
	}
}

ZunoError_t zunoSyncLockRead(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	return (_lock(lpLock, value, SyncModeRead, lpKey));
}

ZunoError_t zunoSyncLockWrite(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	return (_lock(lpLock, value, SyncModeWrite, lpKey));
}

static void _relese(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	volatile uint8_t	*lp;

	lp = &lpLock->bLock;
	_sectionEnter(lp);
	if (lpLock->master == value && lpKey[0] == true) {
		if (lpLock->counter == ((uint16_t)-1))
			lpLock->counter = 0;
		else
			lpLock->counter--;
	}
	_sectionLeave(lp);
}

void zunoSyncReleseRead(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	_relese(lpLock, value, lpKey);
}

void zunoSyncReleseWrite(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	_relese(lpLock, value, lpKey);
}

ZunoError_t zunoSyncOpen(ZunoSync_t *lpLock, SyncMaster_t value, ZunoError_t (*f)(size_t), size_t param, volatile uint8_t *lpKey) {
	SyncMaster_t		master;
	volatile uint8_t	*lp;
	ZunoError_t			ret;
	size_t				bIo;

	bIo = zunoIsIOThread();
	lp = &lpLock->bLock;
	while (0xFF) {
		_sectionEnter(lp);
		if ((master = lpLock->master) == SyncMasterOpenClose) {
			if (bIo == true)
				return (ZunoErrorTredIo);
			_sectionLeave(lp);
			delay(1);
			continue ;
		}
		if (lpKey[0] == true) {
			ret = ZunoErrorSyncAlreadyOpen;
			break ;
		}
		if (master == SyncMasterFree) {
			lpLock->master = SyncMasterOpenClose;
			_sectionLeave(lp);
			if (f != 0 && f(param) != ZunoErrorOk) {
				_sectionEnter(lp);
				lpLock->master = SyncMasterFree;
				ret = ZunoErrorSyncInvalidInit;
				break ;
			}
			else {
				_sectionEnter(lp);
				lpLock->master = value;
				lpLock->master_count++;
				lpKey[0] = true;
				ret = ZunoErrorOk;
				break ;
			}
		}
		else if (master == value) {
			lpLock->master_count++;
			lpKey[0] = true;
			ret = ZunoErrorOk;
			break ;
		}
		else {
			ret = ZunoErrorResourceAlready;
			break ;
		}
	}
	_sectionLeave(lp);
	return (ret);
}

void zunoSyncClose(ZunoSync_t *lpLock, SyncMaster_t value, void (*f)(size_t), size_t param, volatile uint8_t *lpKey) {
	volatile uint8_t	*lp;

	lp = &lpLock->bLock;
	if (_lock(lpLock, value, SyncModeWrite, lpKey) != ZunoErrorOk)
		return ;
	_sectionEnter(lp);
	lpKey[0] = false;
	if (--lpLock->master_count == 0) {
		lpLock->master = SyncMasterOpenClose;
		if (f != 0) {
			_sectionLeave(lp);
			f(param);
			_sectionEnter(lp);
		}
		lpLock->counter = 0;
		lpLock->master = SyncMasterFree;
	}
	_sectionLeave(lp);
}