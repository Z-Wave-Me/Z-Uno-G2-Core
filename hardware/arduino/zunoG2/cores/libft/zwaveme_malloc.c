#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "zwaveme_libft.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct					ZMallocTop_s
{
	uint16_t					alloc_prev;//Если ноль то нечего перед этим листом не выделенно
	uint16_t					alloc_size;
}								ZMallocTop_t;

typedef struct					ZMallocFreeList_s
{
	ZMallocTop_t				top;
	uint16_t					next;
	uint16_t					prev;
}								ZMallocFreeList_t;


#define MALLOC_HEAP_START				((void *)&_heap)
#define MALLOC_HEAP_END					((void *)&__heap_end__)
#define MALLOC_HEAP_SIZE				((size_t)&__heap_size__)
#define MALLOC_STATUS_BUSY				0x8000
#define MALLOC_OFFSET					((size_t)&__bss_start__)

extern unsigned long __bss_start__;
extern unsigned long __heap_start__;
extern unsigned long __heap_end__;
extern unsigned long __heap_size__;

static uint8_t _heap[sizeof(ZMallocFreeList_t)] __attribute__ ((section(".heap")));
static ZMallocFreeList_t *_malloc_free_list = 0;

static size_t _mallocFullSize(size_t size) {
	size = (size + ((sizeof(size_t) - 1) + sizeof(ZMallocTop_t))) & (0 - sizeof(size_t));
	if (size < (sizeof(ZMallocFreeList_t)))
		size = sizeof(ZMallocFreeList_t);
	return (size);
}

static void *_malloc(size_t size) {
	ZMallocFreeList_t					*freeList;
	ZMallocFreeList_t					*list;
	ZMallocFreeList_t					*list_new;
	ZMallocFreeList_t					*list_tmp;
	ZMallocFreeList_t					*list_prev;
	ZMallocFreeList_t					*list_next;
	size_t								min;
	size_t								tempos;
	size_t								size_free;

	if ((freeList = _malloc_free_list) == 0) {
		freeList = (ZMallocFreeList_t *)MALLOC_HEAP_START;
		_malloc_free_list = freeList;
		freeList->top.alloc_size = MALLOC_HEAP_SIZE;
	}
	size = _mallocFullSize(size);
	list = (ZMallocFreeList_t *)MALLOC_OFFSET;
	min = (size_t)(-1);
	while (freeList != (ZMallocFreeList_t *)MALLOC_OFFSET) {
		if ((tempos = freeList->top.alloc_size) >= size && tempos <= min) {
			min = tempos;
			list = freeList;
			if (min == size)
				break ;
		}
		freeList = (ZMallocFreeList_t *)(MALLOC_OFFSET + freeList->next);
	}
	if (list == (ZMallocFreeList_t *)MALLOC_OFFSET)
		return (0);
	if (min >= (size + sizeof(ZMallocFreeList_t))) {
		size_free = min - size;
		list_new = list;
		list_new->top.alloc_size = size_free;
		list = (ZMallocFreeList_t *)((size_t)list + size_free);
		list->top.alloc_prev = size_free;
		list->top.alloc_size = size;
		list_tmp = (ZMallocFreeList_t *)((size_t)list + size);
		if (list_tmp <= (ZMallocFreeList_t *)((size_t)MALLOC_HEAP_END - sizeof(ZMallocFreeList_t)))
			list_tmp->top.alloc_prev = size;
	}
	else {
		list_next = (ZMallocFreeList_t *)(list->next + (size_t)MALLOC_OFFSET);
		list_prev = (ZMallocFreeList_t *)(list->prev + (size_t)MALLOC_OFFSET);
		list_new = (ZMallocFreeList_t *)MALLOC_OFFSET;
		if (list_next != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			list_next->prev = list->prev;
			list_new = list_next;
		}
		if (list_prev != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			list_prev->next = list->next;
			list_new = list_prev;
		}
		_malloc_free_list = list_new;
	}
	list->top.alloc_size = list->top.alloc_size | MALLOC_STATUS_BUSY;
	return ((uint8_t *)list + sizeof(ZMallocTop_t));
}

void *malloc(size_t size) {
	void			*tmp;

	tmp = _malloc(size);
	return (tmp);
}

static void _mallocListMerge(ZMallocFreeList_t *main, ZMallocFreeList_t *extra) {
	ZMallocFreeList_t					*list_next;
	ZMallocFreeList_t					*list_prev;

	main->top.alloc_size = main->top.alloc_size + extra->top.alloc_size;
	list_next = (ZMallocFreeList_t *)(extra->next + (size_t)MALLOC_OFFSET);
	list_prev = (ZMallocFreeList_t *)(extra->prev + (size_t)MALLOC_OFFSET);
	if (list_next != (ZMallocFreeList_t *)MALLOC_OFFSET)
		list_next->prev = extra->prev;
	if (list_prev != (ZMallocFreeList_t *)MALLOC_OFFSET)
		list_prev->next = extra->next;
}

static void _free(void *ptr) {
	ZMallocFreeList_t					*freeList;
	ZMallocFreeList_t					*list;
	ZMallocFreeList_t					*list_tmp;
	size_t								tempos;

	if (ptr <= MALLOC_HEAP_START || ptr >= MALLOC_HEAP_END)
		return ;
	list = (ZMallocFreeList_t *)((uint8_t *)ptr - sizeof(ZMallocTop_t));
	list->top.alloc_size = list->top.alloc_size ^ MALLOC_STATUS_BUSY;
	list->prev = 0;
	if ((freeList = _malloc_free_list) == (ZMallocFreeList_t *)MALLOC_OFFSET)
		list->next = 0;
	else {
		freeList->prev = (size_t)list - (size_t)MALLOC_OFFSET;
		list->next = (size_t)freeList - (size_t)MALLOC_OFFSET;
	}
	while ((tempos = list->top.alloc_prev) != 0) {
		list_tmp = (ZMallocFreeList_t *)((size_t)list - tempos);
		if ((list_tmp->top.alloc_size & MALLOC_STATUS_BUSY) != 0)
			break ;
		_mallocListMerge(list_tmp, list);
		list = list_tmp;
	}
	while (0xFF) {
		list_tmp = (ZMallocFreeList_t *)((size_t)list + list->top.alloc_size);
		if (list_tmp > (ZMallocFreeList_t *)((size_t)MALLOC_HEAP_END - sizeof(ZMallocFreeList_t)) || (list_tmp->top.alloc_size & MALLOC_STATUS_BUSY) != 0)
			break ;
		_mallocListMerge(list, list_tmp);
	}
	_malloc_free_list = list;
}

void free(void *ptr) {
	_free(ptr);
}

void *realloc(void *ptr, size_t size) {
	ZMallocFreeList_t					*list;
	size_t								sizeOld;
	size_t								sizeNew;
	void								*ptrNew;

	if (ptr == 0)
		return (malloc(size));
	if (size == 0) {
		free(ptr);
		return (0);
	}
	sizeNew = _mallocFullSize(size);
	list = (ZMallocFreeList_t *)((uint8_t *)ptr - sizeof(ZMallocTop_t));
	sizeOld = list->top.alloc_size ^ MALLOC_STATUS_BUSY;
	if (sizeOld >= sizeNew)
		return (ptr);
	if ((ptrNew = malloc(sizeNew)) == 0)
		return (0);
	memcpy(ptrNew, ptr, (sizeOld - sizeof(ZMallocTop_t)));
	free(ptr);
	return (ptrNew);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
	size_t						tempos;

	if (__builtin_mul_overflow (nmemb, size, &tempos)) {
		errno = ENOMEM;
		return (0);
	}
	return (realloc(ptr, tempos));
}

void *calloc(size_t nmemb, size_t size) {
	size_t						tempos;
	void						*tmp;

	if (__builtin_mul_overflow (nmemb, size, &tempos)) {
		errno = ENOMEM;
		return (0);
	}
	if ((tmp = malloc(tempos)) == 0)
		return (0);
	memset(tmp, 0, tempos);
	return (tmp);
}

void malloc_stats(void) {
	ZMallocFreeList_t					*freeList;
	size_t								freeBytes;
	size_t								i;

	printf("system bytes     = %10u\n", MALLOC_HEAP_SIZE);
	freeList = _malloc_free_list;
	freeBytes = 0;
	i = 0;
	if (freeList != 0) {
		while (freeList != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			i++;
			freeBytes = freeBytes + freeList->top.alloc_size;
			freeList = (ZMallocFreeList_t *)(MALLOC_OFFSET + freeList->next);
		}
	}
	printf("in use bytes     = %10u\n", MALLOC_HEAP_SIZE - freeBytes);
	printf("free blocks      = %10u\n", i);
}

#ifdef __cplusplus
}
#endif