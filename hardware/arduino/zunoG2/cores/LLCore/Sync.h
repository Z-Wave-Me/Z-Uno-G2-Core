#ifndef SYNC_H
#define SYNC_H

typedef enum							SyncMaster_e
{
	SyncMasterFree,// do not use !!!
	SyncMasterOpenClose,// do not use !!!
	SyncMasterHadwareSerial,
	SyncMasterDht,
	SyncMasterOneWare
}										SyncMaster_t;

typedef struct							ZunoSync_s
{
	volatile void						*handle;
	volatile uint16_t					counter;
	volatile uint8_t					bLock;
	volatile SyncMaster_t				master;
	volatile uint16_t					master_count;
}										ZunoSync_t;

#define ZUNO_SYNC_INIT_DEFAULT			\
{										\
	.handle = 0,						\
	.counter = 0,						\
	.bLock = 0,							\
	.master = SyncMasterFree,			\
	.master_count = 0					\
}

ZunoError_t zunoSyncOpen(ZunoSync_t *lpLock, SyncMaster_t value, ZunoError_t (*f)(size_t), size_t param, volatile uint8_t *lpKey);
void zunoSyncClose(ZunoSync_t *lpLock, SyncMaster_t value, void (*f)(size_t), size_t param, volatile uint8_t *lpKey);

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

#endif // SYNC_H