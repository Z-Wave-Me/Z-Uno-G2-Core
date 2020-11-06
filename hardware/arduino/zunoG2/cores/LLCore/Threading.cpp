#include "Threading.h"

// Mutex
znMutex::znMutex(){
    _handle = zunoSysCall(ZUNO_MSGQUEUE_ALLOC, 4, 1, 1, _xfer_dta, &_queue_data);
}
bool znMutex::lock(uint32_t maximum_timeout){
    uint8_t dta =1;
    if(_handle == NULL)
        return false;

    return zunoSysCall(ZUNO_MSGQUEUE_SEND, 3,  _handle, &dta, maximum_timeout) != (void*)0;
}
bool znMutex::try_lock(){
    return lock(SYNCTIMEOUT_IMMIDIATELY);
}
void znMutex::unlock(){
    uint8_t dta;
    if(_handle == NULL)
        return;
    zunoSysCall(ZUNO_MSGQUEUE_RCV, 3, _handle, &dta, 0);
}

// Semaphore
znSemaphore::znSemaphore(uint8_t counter){
    if(counter > MAX_SEMAPHORE_COUNT)
        counter = MAX_SEMAPHORE_COUNT;
     _basecounter = counter;
     _handle = zunoSysCall(ZUNO_MSGQUEUE_ALLOC, 4, counter, 1, _xfer_dta, &_queue_data);
}
bool znSemaphore::acquire(uint8_t upd, uint32_t maximum_timeout){
    uint8_t count = 0;
    uint8_t dta = 1;
    if(upd == 0)
        return false;
    uint32_t timeout = maximum_timeout;
    
    while(count < upd){
        uint32_t starttime = millis();
        if(zunoSysCall(ZUNO_MSGQUEUE_SEND, 3,  _handle, &dta, timeout) != (void*)0)
            break;
        count++;
        if(millis() > (starttime + timeout)){
            break;
        }
        timeout -= (millis() - starttime);
    }
    if(count != upd){
        while(count--){
            zunoSysCall(ZUNO_MSGQUEUE_RCV, 3, _handle, &dta, 0);
        }
        return false;
    }
    return true;
}
bool znSemaphore::try_acquire(uint8_t upd){
    return acquire(upd, SYNCTIMEOUT_IMMIDIATELY);
}
void znSemaphore::release(uint8_t upd){
    uint8_t count = 0;
    uint8_t dta = 1;
    if(upd == 0)
        return;
    while(count<upd){
        zunoSysCall(ZUNO_MSGQUEUE_RCV, 3, _handle, &dta, 0);
        count++;
    }
}
// Message Queue
znMessageQueue::znMessageQueue(uint32_t msg_size, uint32_t queuesize, void * queuedata){
     _handle = zunoSysCall(ZUNO_MSGQUEUE_ALLOC, 4, queuesize, queuesize, queuedata, _queue_data);
}
bool znMessageQueue::send(void * msg, uint32_t wait_time){
    return zunoSysCall(ZUNO_MSGQUEUE_SEND, 3,  _handle, msg, wait_time) != (void*)0;
            
}
bool znMessageQueue::receive(void * msg, uint32_t wait_time){
    return zunoSysCall(ZUNO_MSGQUEUE_RCV, 3,  _handle, msg, wait_time) != (void*)0;
}
// Thread
znThread::znThread(threadcodefunc_t  func, uint32_t stack_size, uint32_t * stack, void * param ){
    _handle = zunoSysCall(ZUNO_THREAD_CREATE, 5, func, stack_size, stack, &_th_data, param);

}
znThread::znThread(uint32_t stack_size, uint32_t * stack) : _stack_size(stack_size), _stack(stack) {
    _handle = NULL;
}
void znThread::start(threadcodefunc_t func, void * param ){
    if(_handle == NULL){
        _handle = zunoSysCall(ZUNO_THREAD_CREATE, 5, func, _stack_size, _stack, &_th_data, param);
    }
}
void znThread::suspend(){
    zunoSysCall(ZUNO_THREAD_SUSPEND, 1, _handle);
}
void znThread::resume(){
    zunoSysCall(ZUNO_THREAD_RESUME, 1, _handle);
}
// C API
void * zunoGetCurrentThreadHandle(){
    return zunoSysCall(ZUNO_THREAD_GETCURRENTHANDLE, 0);
}
void   zunoSuspendThread(void * handle){
    zunoSysCall(ZUNO_THREAD_SUSPEND, 1, handle);
}
void   zunoResumeThread(void * handle){
    zunoSysCall(ZUNO_THREAD_RESUME, 1, handle);
}