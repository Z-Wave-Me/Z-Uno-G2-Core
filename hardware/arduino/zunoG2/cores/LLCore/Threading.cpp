#include "Threading.h"
#include "LinkedList.h"
// -----------------------------------------------------------------------
// Mutex
znMutex::znMutex() {
    _handle = zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_ALLOC, 4, 1, 1, _xfer_dta, &_queue_data);
}

bool znMutex::lock(size_t maximum_timeout) {
	size_t			dta;
	void			*handle;

	if((handle = this->_handle) == NULL)
		return false;
	dta = 1;
	return zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_SEND, 3, handle, &dta, maximum_timeout) != (void*)0;
}

void znMutex::unlock() {
	size_t			dta;
	void			*handle;

	if((handle = this->_handle) == NULL)
		return;
	zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_RCV, 3, handle, &dta, 0);
}



// -----------------------------------------------------------------------
// Semaphore
znSemaphore::znSemaphore(uint8_t counter) {
    if(counter > MAX_SEMAPHORE_COUNT)
        counter = MAX_SEMAPHORE_COUNT;
     _basecounter = counter;
     _handle = zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_ALLOC, 4, counter, 1, _xfer_dta, &_queue_data);
}

bool znSemaphore::acquire(uint8_t upd, uint32_t maximum_timeout) {
	size_t				count = 0;
	size_t				dta = 1;
	void				*handle;
	size_t				timeout = maximum_timeout;

	if(upd == 0)
		return (false);
	handle = this->_handle;
	while(count < upd) {
		uint32_t starttime = millis();
		if(zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_SEND, 3, handle, &dta, timeout) != (void*)0)
			break;
		count++;
		if(millis() > (starttime + timeout)) {
			break;
		}
		timeout -= (millis() - starttime);
	}
	if(count != upd) {
		while(count--) {
			zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_RCV, 3, handle, &dta, 0);
		}
		return false;
	}
	return true;
}

void znSemaphore::release(uint8_t upd) {
    size_t count = 0;
    size_t dta = 1;
    if(upd == 0)
        return;
    while(count<upd) {
        zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_RCV, 3, _handle, &dta, 0);
        count++;
    }
}



// -----------------------------------------------------------------------
//Message Queue
znMessageQueue::znMessageQueue(uint32_t msg_size, uint32_t queuesize, void *queuedata) {
    _handle = zunoSysCall(ZUNO_SYSFUNC_MSGQUEUE_ALLOC, 4, queuesize, queuesize, queuedata, _queue_data);
	(void)msg_size;
}



// -----------------------------------------------------------------------
//Thread
static ZNLinkedList_t * g_user_threadlst = NULL;
static void * g_timerThread = NULL;
static void * g_commandThread = NULL;
void * zunoGetSysThreadHandle(ZunoSysThreadType_t type){
	switch(type){
		case SYS_THREAD_MAIN:
			return g_zuno_sys->hMainThread;
		case SYS_THREAD_TIMER:
			return g_timerThread;
		case SYS_THREAD_COMMAND_HANDLER:
			return g_commandThread;
		case SYS_THREAD_IO:
			return g_zuno_sys->hIOThread;
	}
	return NULL;
}
void _zunoRegisterTimerThread(){
	g_timerThread = zunoGetCurrentThreadHandle();
}
void _zunoRegisterCommandThread(){
	g_commandThread = zunoGetCurrentThreadHandle();
};
void * zunoCreateCustomThread(threadcodefunc_t  func, uint32_t stack_size, uint32_t *stack, void *param, _znSysThData_t * thdata ){
	void * handle =  zunoSysCall(ZUNO_SYSFUNC_THREAD_CREATE, 5, func, stack_size, stack, thdata, param);
	if(handle != NULL){
		znllPushBack(&g_user_threadlst, handle);
	}
	return handle;
}
bool zunoIsCustomThread(void * handle){
	if(handle == NULL){
		handle = zunoGetCurrentThreadHandle();
	}
	for(ZNLinkedList_t * it = g_user_threadlst; it; it = it->next)
		if(it->data == handle)
			return true;
	return false;
}
bool zunoIsMainThread(void * handle){
	if(handle == NULL){
		handle = zunoGetCurrentThreadHandle();
	}
	return (handle == g_zuno_sys->hMainThread);
}
bool zunoIsIOThread(void * handle){
	
	if(handle == NULL){
		handle = zunoGetCurrentThreadHandle();
	}
	return (handle == g_zuno_sys->hIOThread);

}
bool zunoIsSystemThread(void * handle){

	if(handle == NULL){
		handle = zunoGetCurrentThreadHandle();
	}
	#if defined(NO_SYS_THREAD)
	#pragma message "SystemThread: Usecured DGB mode!!!"
	return false;
	#elif defined(SYSTHREAD_INT_ONLY)
	#pragma message "SystemThread: INT"
	return zunoIsIOThread(handle); 
	#elif defined(SYSTHREAD_TIMER_AND_INT)
	#pragma message "SystemThread: INT + TIMER"
	return zunoIsIOThread(handle) || (handle == g_timerThread); 
	#else
	#pragma message "SystemThread: !UserThread"
	return (!zunoIsMainThread(handle)) && (!zunoIsCustomThread(handle));
	#endif
	
}
znThread::znThread(threadcodefunc_t  func, uint32_t stack_size, uint32_t *stack, void *param ) {
	stack[0x0] = 0x0;
	stack++;
	stack_size--;
	_handle = zunoCreateCustomThread(func, stack_size, stack, param, &_th_data);//zunoSysCall(ZUNO_SYSFUNC_THREAD_CREATE, 5, func, stack_size, stack, &_th_data, param);
}

znThread::znThread(uint32_t stack_size, uint32_t *stack) : _stack_size(stack_size), _stack(stack) {
	_handle = NULL;
}

void znThread::start(threadcodefunc_t func, void *param ) {
	if(_handle == NULL){
		_handle = zunoCreateCustomThread(func, _stack_size, _stack, param, &_th_data);//zunoSysCall(ZUNO_SYSFUNC_THREAD_CREATE, 5, func, _stack_size, _stack, &_th_data, param);
	}
}

#ifdef __cplusplus
extern "C" {
#endif

void __malloc_lock(void) __attribute__((used));
void __malloc_lock(void) {
	zunoEnterCritical();
}

void __malloc_unlock(void) __attribute__((used));
void __malloc_unlock(void) {
	zunoExitCritical();
}

#ifdef __cplusplus
}
#endif
