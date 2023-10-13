#ifndef ZUNO_SIMPLE_LINKEDLIST
#define ZUNO_SIMPLE_LINKEDLIST
#include <Arduino.h>
typedef struct ZNLinkedList_s{
    void * data;
    ZNLinkedList_s * next;
} ZNLinkedList_t;
bool znllPushBack(ZNLinkedList_t** l, void * d);
void * znllRemove(ZNLinkedList_t** l, int index);
void * znllRemoveP(ZNLinkedList_t** l, void * d);

int znllCount(ZNLinkedList_t* l);
#endif // ZUNO_SIMPLE_LINKEDLIST