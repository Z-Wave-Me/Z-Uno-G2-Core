#include "Arduino.h"
#include "CrtxGcc.h"
#include "CrtxCore.h"
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
ZunoSync_t gSyncCSEN = ZUNO_SYNC_INIT_DEFAULT;

typedef enum							SyncMode_e
{
	SyncModeWrite = 1,
	SyncModeRead
}										SyncMode_t;

#define ZUNO_SYNC_NO_TYPE			0x0
#define ZUNO_SYNC_FALSE				0x1
#define ZUNO_SYNC_TRUE				0x2

#define ZUNO_SYNC_SPIN_COUNT		0xA

static size_t _wait(ZunoSync_t *lpLock, SyncMaster_t value, SyncMode_t mode, volatile uint8_t *lpKey) {
	volatile uint8_t		counter;

	if (lpLock->master != value || lpKey[0] == false)
		return (ZUNO_SYNC_NO_TYPE);
	counter = lpLock->counter;
	if (mode == SyncModeWrite) {
		if (counter == 0) {
			lpLock->counter = ((uint8_t)-1);
			return (ZUNO_SYNC_TRUE);
		}
	} else if (counter != ((uint8_t)-1)) {
		lpLock->counter++;
		return (ZUNO_SYNC_TRUE);
	}
	return (ZUNO_SYNC_FALSE);
}

static ZunoError_t _lock(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey, SyncMode_t mode) {
	size_t				out;
	size_t				i;
	
	if (zunoIsIOThread() == true)
		return (ZunoErrorTredIo);
	while (0xFF) {
		i = 0;
		while (i++ < ZUNO_SYNC_SPIN_COUNT) {
			zunoEnterCritical();
			out = _wait(lpLock, value, mode, lpKey);
			zunoExitCritical();
			if (out == ZUNO_SYNC_NO_TYPE)
				return (ZunoErrorSyncInvalidType);
			if (out == ZUNO_SYNC_TRUE)
				return (ZunoErrorOk);
		}
		delay(1);
	}
}

ZunoError_t zunoSyncLockRead(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	return (_lock(lpLock, value, lpKey, SyncModeRead));
}

ZunoError_t zunoSyncLockWrite(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	return (_lock(lpLock, value, lpKey, SyncModeWrite));
}

static void _relese(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {

	if (zunoIsIOThread() == true)
		return ;
	zunoEnterCritical();
	if (lpLock->master == value && lpKey[0] == true) {
		if (lpLock->counter == ((uint8_t)-1))
			lpLock->counter = 0;
		else
			lpLock->counter--;
	}
	zunoExitCritical();
}

void zunoSyncReleseRead(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	_relese(lpLock, value, lpKey);
}

void zunoSyncReleseWrite(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey) {
	_relese(lpLock, value, lpKey);
}

ZunoError_t zunoSyncOpen(ZunoSync_t *lpLock, SyncMaster_t value, ZunoError_t (*f)(size_t), size_t param, volatile uint8_t *lpKey) {
	SyncMaster_t		master;
	ZunoError_t			ret;

	if (zunoIsIOThread() == true)
		return (ZunoErrorTredIo);
	while (0xFF) {
		zunoEnterCritical();
		if ((master = lpLock->master) == SyncMasterOpenClose) {
			zunoExitCritical();
			delay(1);
			continue ;
		}
		if (lpKey[0] == true) {
			zunoExitCritical();
			return (_lock(lpLock, value, lpKey, SyncModeWrite));
			break ;
		}
		if (master == SyncMasterFree) {
			lpLock->master = SyncMasterOpenClose;
			zunoExitCritical();
			if (f != 0 && f(param) != ZunoErrorOk) {
				zunoEnterCritical();
				lpLock->master = SyncMasterFree;
				ret = ZunoErrorSyncInvalidInit;
				break ;
			}
			else {
				zunoEnterCritical();
				lpLock->master = value;
				lpLock->master_count++;
				lpLock->counter = ((uint8_t)-1);
				lpKey[0] = true;
				ret = ZunoErrorOk;
				break ;
			}
		}
		else if (master == value) {
			lpLock->master_count++;
			lpLock->counter = ((uint8_t)-1);
			lpKey[0] = true;
			ret = ZunoErrorOk;
			break ;
		}
		else {
			ret = ZunoErrorResourceAlready;
			break ;
		}
	}
	zunoExitCritical();
	return (ret);
}

ZunoError_t zunoSyncClose(ZunoSync_t *lpLock, SyncMaster_t value, ZunoError_t (*f)(size_t), size_t param, volatile uint8_t *lpKey) {
	ZunoError_t			ret;

	if (zunoIsIOThread() == true)
		return (ZunoErrorTredIo);
	if ((ret = _lock(lpLock, value, lpKey, SyncModeWrite)) != ZunoErrorOk)
		return (ret);
	zunoEnterCritical();
	lpKey[0] = false;
	if (--lpLock->master_count == 0) {
		lpLock->master = SyncMasterOpenClose;
		zunoExitCritical();
		if (f != 0 && (ret = f(param)) != ZunoErrorOk) {
			zunoEnterCritical();
			lpLock->master_count++;
			lpLock->master = value;
		}
		else {
			zunoEnterCritical();
			lpLock->counter = 0;
			lpLock->master = SyncMasterFree;
		}
	}
	zunoExitCritical();
	return (ret);
}