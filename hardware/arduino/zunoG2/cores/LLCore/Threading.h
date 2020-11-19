#ifndef ZUNO_THREADING
#define ZUNO_THREADING
#include <Arduino.h>
#define SYNCTIMEOUT_INFINITY        0xFFFFFFF
#define SYNCTIMEOUT_IMMIDIATELY     0
#define MAX_SEMAPHORE_COUNT         0x10 

typedef void (*threadcodefunc_t) (void *param);

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
		bool								lock(size_t maximum_timeout = SYNCTIMEOUT_INFINITY);
		inline bool							try_lock() {return (this->lock(SYNCTIMEOUT_IMMIDIATELY));};
		void								unlock();
		inline bool							isValid() {return _handle != NULL; };
	private:
		void *_handle;
		_znSysQData_t _queue_data;
		uint8_t _xfer_dta[1];

};
class znSemaphore{
	public:
		znSemaphore(uint8_t counter);
		bool								acquire(uint8_t upd = 1, uint32_t maximum_timeout = SYNCTIMEOUT_INFINITY);
		inline bool							try_acquire(uint8_t upd = 1) {return (acquire(upd, SYNCTIMEOUT_IMMIDIATELY));};
		void								release(uint8_t upd = 1);
	private:
		void					*_handle;
		_znSysQData_t			_queue_data;
		uint8_t					_xfer_dta[MAX_SEMAPHORE_COUNT];
		uint8_t					_basecounter;
};

class znMessageQueue{

	public:
		znMessageQueue(uint32_t msg_size, uint32_t queuesize, void *queuedata);
		inline bool							send(void *msg, uint32_t wait_time = SYNCTIMEOUT_INFINITY) {return zunoSysCall(ZUNO_MSGQUEUE_SEND, 3, _handle, msg, wait_time) != (void*)0;};
		inline bool							receive(void *msg, uint32_t wait_time = SYNCTIMEOUT_INFINITY) {return zunoSysCall(ZUNO_MSGQUEUE_RCV, 3, _handle, msg, wait_time) != (void*)0;};
	private:
		void *_handle;
		_znSysQData_t  _queue_data;
};
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// ZUNO THREAD Implementation
class znThread {
	public:
		znThread(threadcodefunc_t  func, uint32_t stack_size, uint32_t *stack, void *param = NULL);
		znThread(uint32_t stack_size, uint32_t *stack);
		void								start(threadcodefunc_t  func, void *param = NULL);
		inline void							suspend() {zunoSysCall(ZUNO_THREAD_SUSPEND, 1, _handle);};
		inline void							resume() {zunoSysCall(ZUNO_THREAD_RESUME, 1, _handle);};
		inline bool							isValid() {return _handle != NULL;};
		inline void							*getHandle() {return _handle; };
	private:
		uint32_t					_stack_size;
		uint32_t					*_stack;
		void						*_handle;
		_znSysThData_t				_th_data;
};

// C API
inline void *zunoGetCurrentThreadHandle() {
	return zunoSysCall(ZUNO_THREAD_GETCURRENTHANDLE, 0);
}

inline void zunoSuspendThread(void *handle) {
	zunoSysCall(ZUNO_THREAD_SUSPEND, 1, handle);
}

inline void zunoResumeThread(void *handle) {
	zunoSysCall(ZUNO_THREAD_RESUME, 1, handle);
}
inline bool zunoThreadIsRunning(void *handle){
    return (bool)zunoSysCall(ZUNO_THREAD_ISRUNNING, 1, handle);
}
inline bool zunoIsIOThread(){
	return (g_zuno_sys->hIOThread == zunoSysCall(ZUNO_THREAD_GETCURRENTHANDLE, 0));
}
inline void zunoEnterCritical(){
	zunoSysCall(ZUNO_ENTER_CRITICAL, 0);
}
inline void zunoExitCritical(){
	zunoSysCall(ZUNO_EXIT_CRITICAL, 0);
}
//disable interrupts
inline void noInterrupts(){
	zunoEnterCritical();
};
//inable interrupts
inline void interrupts(){
	zunoExitCritical();
};

#endif // ZUNO_THREADING