#include "LinkedList.h"

bool znllPushBack(ZNLinkedList_t** l,void * d){
    ZNLinkedList_t * el = (ZNLinkedList_t *)malloc(sizeof(ZNLinkedList_t));
    if(el == NULL)
        return false;
    el->data = d;
    el->next = NULL;
    if (*l == NULL){
        *l = el;
        return true;
    }
    ZNLinkedList_t* e = *l;
    while(e->next != NULL) 
        e = e->next;
    e->next = el;
    return true;
}
void * znllRemove(ZNLinkedList_t** l, int index){
    ZNLinkedList_t* e = *l;
    ZNLinkedList_t* p = NULL;
    int i =0;
    if(index <  0){
        index = znllCount(*l)+index;
        if(index < 0)
            return NULL;
    }
    while(i != index) {
        if(e == NULL)
            return NULL;
        p = e;
        e = e->next;
        i++;
    }
    void * d = e->data;
    if(p != NULL){
        p->next = e->next;
    } else {
        *l = e->next;
    }
    return d;
}
int znllCount(ZNLinkedList_t* l){
    size_t count = 0;
    ZNLinkedList_t* e = l;
    while(e != NULL) {
        count++;
        e = e->next;
    }
    return count;
}