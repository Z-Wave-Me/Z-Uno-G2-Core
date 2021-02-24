#ifndef SYNC_H
#define SYNC_H

typedef enum							SyncMaster_e
{
	SyncMasterFree,// do not use !!!
	SyncMasterOpenClose,// do not use !!!
	SyncMasterHadwareSerial,
	SyncMasterGPT,
	SyncMasterTone,
	SyncMasterI2c,
	SyncMasterSpi,
	SyncMasterNeoPixel,
	SyncMasterSomfy,
	SyncMasterNeptun,
	SyncMasterPwm,
	SyncMasterBtn,
	SyncMasterDht
}										SyncMaster_t;

typedef struct							ZunoSync_s
{
	volatile SyncMaster_t				master;
	volatile uint8_t					master_count;
	volatile uint8_t					counter;
}										ZunoSync_t;

#define ZUNO_SYNC_INIT_DEFAULT			\
{										\
	.master = SyncMasterFree,			\
	.master_count = 0,					\
	.counter = 0						\
}

#define ZUNO_SYNC_INIT_DEFAULT_OPEN(valMaster)	\
{												\
	.master = valMaster,						\
	.master_count = 1,							\
	.counter = 0								\
}

ZunoError_t zunoSyncOpen(ZunoSync_t *lpLock, SyncMaster_t value, ZunoError_t (*f)(size_t), size_t param, volatile uint8_t *lpKey);
ZunoError_t zunoSyncClose(ZunoSync_t *lpLock, SyncMaster_t value, ZunoError_t (*f)(size_t), size_t param, volatile uint8_t *lpKey);

ZunoError_t zunoSyncLockRead(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey);
void zunoSyncReleseRead(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey);

ZunoError_t zunoSyncLockWrite(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey);
void zunoSyncReleseWrite(ZunoSync_t *lpLock, SyncMaster_t value, volatile uint8_t *lpKey);

extern ZunoSync_t gSyncUSART0;
extern ZunoSync_t gSyncUSART1;
extern ZunoSync_t gSyncUSART2;
extern ZunoSync_t gSyncTIMER0;
extern ZunoSync_t gSyncTIMER1;
extern ZunoSync_t gSyncWTIMER0;
extern ZunoSync_t gSyncIC0;
extern ZunoSync_t gSyncIC1;
extern ZunoSync_t gSyncCSEN;

#endif // SYNC_H