#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "zwaveme_libft.h"

#ifdef __cplusplus
extern "C" {
#endif

// extern unsigned long __HeapBase;
// extern unsigned long __HeapLimit;

// void *_sbrk(intptr_t delta) {
// 	static uint8_t		*heap_end = 0;
// 	uint8_t				*prev_heap_end;

// 	if (heap_end == 0)
// 		heap_end = (uint8_t *)&__HeapBase;
// 	prev_heap_end = heap_end;
// 	delta = ((delta + (sizeof(size_t) - 1)) & (0 - sizeof(size_t)));
// 	if (heap_end + delta > (uint8_t *)&__HeapLimit) {
// 		errno = ENOMEM;
// 		return (void *) -1;
// 	}
// 	heap_end = heap_end + delta;
// 	return (prev_heap_end);
// }

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

	if ((freeList = _malloc_free_list) == 0x0) {
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
		if (list_next != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			list_next->prev = list->prev;
		}
		if (list_prev != (ZMallocFreeList_t *)MALLOC_OFFSET) {
			list_prev->next = list->next;
		}
		else
			_malloc_free_list = list_next;
	}
	list->top.alloc_size = list->top.alloc_size | MALLOC_STATUS_BUSY;
	return ((uint8_t *)list + sizeof(ZMallocTop_t));
}

void __malloc_lock(void);
void __malloc_unlock(void);

void *malloc(size_t size) {
	void			*tmp;

	__malloc_lock();
	tmp = _malloc(size);
	__malloc_unlock();
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
	list->prev = 0x0;
	freeList = _malloc_free_list;
	list->next = (size_t)freeList - (size_t)MALLOC_OFFSET;
	if (freeList != (ZMallocFreeList_t *)MALLOC_OFFSET)
		freeList->prev = (size_t)list - (size_t)MALLOC_OFFSET;
	while ((tempos = list->top.alloc_prev) != 0x0) {
		list_tmp = (ZMallocFreeList_t *)((size_t)list - tempos);
		if ((list_tmp->top.alloc_size & MALLOC_STATUS_BUSY) != 0x0)
			break ;
		list = list_tmp;
	}
	_malloc_free_list = list;
	while (0xFF) {
		list_tmp = (ZMallocFreeList_t *)((size_t)list + list->top.alloc_size);
		if (list_tmp > (ZMallocFreeList_t *)((size_t)MALLOC_HEAP_END - sizeof(ZMallocFreeList_t)))
			break ;
		if ((list_tmp->top.alloc_size & MALLOC_STATUS_BUSY) != 0x0) {
			list_tmp->top.alloc_prev = list->top.alloc_size;
			break ;
		}
		_mallocListMerge(list, list_tmp);
	}

}

void free(void *ptr) {
	__malloc_lock();
	_free(ptr);
	__malloc_unlock();
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
	const ZMallocFreeList_t				*list;
	size_t								free_block;
	size_t								free_bytes;
	size_t								use_block;
	size_t								use_bytes;
	size_t								alloc_size;

	printf("system bytes     = %10u\n", MALLOC_HEAP_SIZE);
	list = (const ZMallocFreeList_t *)MALLOC_HEAP_START;
	free_block = 0x0;
	free_bytes = 0x0;
	use_block = 0x0;
	use_bytes = 0x0;
	if (_malloc_free_list != NULL) {
		while (list < (const ZMallocFreeList_t *)MALLOC_HEAP_END) {
			alloc_size = list->top.alloc_size;
			if ((alloc_size & MALLOC_STATUS_BUSY) != 0x0) {
				alloc_size = alloc_size ^ MALLOC_STATUS_BUSY;
				use_block++;
				use_bytes = use_bytes + alloc_size;
			}
			else {
				free_block++;
				free_bytes = free_bytes + alloc_size;
			}
			list = (const ZMallocFreeList_t *)((uint8_t *)list + alloc_size);
		}
	}
	printf("in use bytes     = %10u\n", use_bytes);
	printf("use blocks       = %10u\n", use_block);
	printf("in free bytes    = %10u\n", free_bytes);
	printf("free blocks      = %10u\n", free_block);
}

#ifdef __cplusplus
}
#endif
