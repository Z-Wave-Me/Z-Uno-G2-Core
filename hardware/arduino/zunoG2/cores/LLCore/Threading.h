#ifndef ZUNO_THREADING
#define ZUNO_THREADING
#include <Arduino.h>
#define SYNCTIMEOUT_INFINITY        0xFFFFFFF
#define SYNCTIMEOUT_IMMIDIATELY     0
#define MAX_SEMAPHORE_COUNT         0x10 

typedef void (*threadcodefunc_t) (void * param);
// -----------------------------------------------------------------------
// SYSTEM internal structs. Depend on RTOS release
// Do not modify!!!
typedef struct _znSysQData_s{
    uint8_t __data[0x48];
}_znSysQData_t;
typedef struct _znSysThData_s{
    uint8_t __data[0x4c];
}_znSysThData_t;
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// SYNCRONIZATION PRIMITIVES
class znMutex{
   public:
        znMutex();
        bool lock(uint32_t maximum_timeout = SYNCTIMEOUT_INFINITY);
        bool try_lock();
        void unlock();
        bool isValid(){return _handle != NULL; };
    private:
        void * _handle;
        _znSysQData_t _queue_data;
        uint8_t _xfer_dta[1];

};
class znSemaphore{
    public:
        znSemaphore(uint8_t counter);
        bool acquire(uint8_t upd = 1, uint32_t maximum_timeout = SYNCTIMEOUT_INFINITY);
        bool try_acquire(uint8_t upd = 1);
        void release(uint8_t upd = 1);
    private:
        uint8_t _basecounter;
        void * _handle;
        _znSysQData_t _queue_data;
        uint8_t _xfer_dta[MAX_SEMAPHORE_COUNT];
};

class znMessageQueue{

    public:
       znMessageQueue(uint32_t msg_size, uint32_t queuesize, void * queuedata);
       bool send(void * msg, uint32_t wait_time = SYNCTIMEOUT_INFINITY);
       bool receive(void * msg, uint32_t wait_time = SYNCTIMEOUT_INFINITY);
    private:
         void * _handle;
         _znSysQData_t  _queue_data;
};
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// ZUNO THREAD Implementation
class znThread{
    public:
        znThread(threadcodefunc_t  func, uint32_t stack_size, uint32_t * stack, void * param = NULL);
        znThread(uint32_t stack_size, uint32_t * stack);
        void start(threadcodefunc_t  func, void * param = NULL);
        void suspend();
        void resume();
        bool isValid(){return _handle != NULL; };
    private:
       uint32_t  _stack_size;
       uint32_t * _stack;
       void * _handle;
       _znSysThData_t _th_data;
};

#endif // ZUNO_THREADING