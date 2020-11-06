#ifndef SYNC_H
#define SYNC_H

typedef enum							SyncMaster_e
{
	SyncMasterFree,
	SyncMasterHadwareSerial
}										SyncMaster_t;

typedef struct							ZunoSync_s
{
	volatile void						*handle;
	volatile uint16_t					counter;
	volatile uint8_t					bLock;
	volatile SyncMaster_t				master;
}										ZunoSync_t;

#define ZUNO_SYNC_INIT_DEFAULT			\
{										\
	.handle = 0,						\
	.counter = 0,						\
	.bLock = 0,							\
	.master = SyncMasterFree			\
}

SyncMaster_t zunoSyncOpen(ZunoSync_t *lpLock, SyncMaster_t value);
void zunoSyncClose(ZunoSync_t *lpLock, SyncMaster_t value);

ZunoError_t zunoSyncLockRead(ZunoSync_t *lpLock, SyncMaster_t value);
void zunoSyncReleseRead(ZunoSync_t *lpLock, SyncMaster_t value);

ZunoError_t zunoSyncLockWrite(ZunoSync_t *lpLock, SyncMaster_t value);
void zunoSyncReleseWrite(ZunoSync_t *lpLock, SyncMaster_t value);

extern ZunoSync_t gSyncUSART0;

#endif // SYNC_H