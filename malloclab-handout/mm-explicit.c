/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  Blocks are never coalesced or reused.  The size of
 * a block is found at the first aligned word before the block (we need
 * it for realloc).
 *
 * This code is correct and blazingly fast, but very bad usage-wise since
 * it never frees anything.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"


/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
//#define DEBUG
#ifdef DEBUG
#define dbg_printf(...) printf(__VA_ARGS__)
#else
#define dbg_printf(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define CHUNKSIZE (1<<8)

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE SIZE_T_SIZE
#define DSIZE (2*WSIZE)
#define OVERHEAD (2*DSIZE)
#define MIN_BLOCK_SIZE (ALIGN(OVERHEAD+1))


typedef size_t word_t;

typedef unsigned int bool;

typedef struct block {
    word_t header;
    void *next;
    void *prev;
    char payload[0];
} block_t;

static block_t *heap_listp = NULL;

static block_t *free_listp = NULL;

static block_t *extend_heap(size_t size);

static block_t *coalesce(block_t *block);

static block_t *find_fit(size_t size);

static void place(block_t *block, size_t size);

static block_t *find_next(block_t *block);

static block_t *find_prev(block_t *block);

static word_t pack(size_t size, bool alloc);

static void write_header(block_t *block, size_t size, bool alloc);

static void write_footer(block_t *block);

static int get_alloc(word_t word);

static size_t get_size(word_t word);

static void *header_to_payload(block_t *block);

static block_t *payload_to_header(void *payload);

static size_t round_up(size_t size, size_t n);

static size_t max(size_t x, size_t y);

static void insert_block(block_t *block);

static void remove_block(block_t *block);

static block_t *find_free_next(block_t *block);

static block_t *find_free_prev(block_t *block);

static size_t find_count = 0;
static size_t block_count = 0;
//static unsigned int times=0;
/*
 * mm_init - Called when a new trace starts.
 */
int mm_init(void)
{
    block_t *block;
    word_t *start = (word_t *) mem_sbrk(2 * WSIZE);
    if (start == (void *) -1) {
        return -1;
    }

    start[0] = pack(WSIZE, 1);
    start[1] = pack(0, 1);

    heap_listp = (block_t *) (start + 1);
    free_listp = NULL;

    if ((block = extend_heap(CHUNKSIZE)) == NULL) {
        return -1;
    }
//    mm_checkheap(__LINE__);
    insert_block(block);
//    mm_checkheap(__LINE__);
    return 0;
}

/*
 * malloc - Allocate a block by incrementing the brk pointer.
 *      Always allocate a block whose size is a multiple of the alignment.
 */
void *malloc(size_t size)
{
    dbg_printf("find count %zu, block count %zu\n", find_count, block_count);
//    mm_checkheap(__LINE__);
    size_t asize, extendsize;
    void *bp = NULL;
    block_t *block;

    if (heap_listp == NULL) // Initialize heap if it isn't initialized
    {
        mm_init();
    }

    if (size == 0) {
        return bp;
    }

    asize = round_up(max(size + DSIZE, MIN_BLOCK_SIZE), ALIGNMENT);
    if ((block = find_fit(asize)) == NULL) {
        extendsize = max(CHUNKSIZE, asize);
        block = extend_heap(extendsize);
        if (block == NULL) {
            return bp;
        }

        insert_block(block);
//        mm_checkheap(__LINE__);
    }
    remove_block(block);
//    mm_checkheap(__LINE__);

    place(block, asize);
    bp = header_to_payload(block);
//    mm_checkheap(__LINE__);
    return bp;
}

/*
 * free - We don't know how to free a block.  So we ignore this call.
 *      Computers have big memories; surely it won't be a problem.
 */
void free(void *ptr)
{
//    dbg_printf("free %p\n", ptr);
//    mm_checkheap(__LINE__);
    block_t *block;
    size_t size;

    if (ptr == NULL)
        return;

    block = payload_to_header(ptr);
    size = get_size(block->header);

    write_header(block, size, 0);
    write_footer(block);

//    mm_checkheap(__LINE__);

    block = coalesce(block);
//    mm_checkheap(__LINE__);

    insert_block(block);

//    mm_checkheap(__LINE__);
}

/*
 * realloc - Change the size of the block by mallocing a new block,
 *      copying its data, and freeing the old block.  I'm too lazy
 *      to do better.
 */
void *realloc(void *oldptr, size_t size)
{
    size_t oldsize;
    void *newptr;
    block_t *oldblock;

    /* If size == 0 then this is just free, and we return NULL. */
    if (size == 0) {
        free(oldptr);
        return NULL;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if (oldptr == NULL) {
        return malloc(size);
    }

    newptr = malloc(size);

    /* If malloc fails the original block is left untouched  */
    if (!newptr) {
        return NULL;
    }

    /* Copy the old data. */
    oldblock = payload_to_header(oldptr);
    oldsize = get_size(oldblock->header);

    if (size < oldsize) oldsize = size;
    memcpy(newptr, oldptr, oldsize);

    /* Free the old block. */
    free(oldptr);

    return newptr;
}

/*
 * calloc - Allocate the block and set it to zero.
 */
void *calloc(size_t nmemb, size_t size)
{
    size_t bytes = nmemb * size;
    void *newptr;

    if (bytes / nmemb != size)
        return NULL;

    newptr = malloc(bytes);
    if (newptr == NULL)
        return NULL;

    memset(newptr, 0, bytes);

    return newptr;
}

static size_t round_up(size_t size, size_t n)
{
    return n * ((size + n - 1) / n);
}

static block_t *payload_to_header(void *bp)
{
    return (block_t *) (((char *) bp) - WSIZE);
}

static void *header_to_payload(block_t *block)
{
    return (void *) (((char *) block) + WSIZE);
}

static size_t get_size(word_t word)
{
    return (word & ~((word_t) 0x7));
}

static int get_alloc(word_t word)
{
    return (word & ((word_t) 0x1));
}

static void write_header(block_t *block, size_t size, bool alloc)
{
    block->header = pack(size, alloc);
}

static void write_footer(block_t *block)
{
    size_t size = get_size(block->header);
    bool alloc = get_alloc(block->header);
    word_t *footerp = (word_t *) ((char *) block + size - WSIZE);

    *footerp = pack(size, alloc);
}

static block_t *find_next(block_t *block)
{
    block_t *block_next = (block_t *) (((char *) block) +
                                       get_size(block->header));
    return block_next;
}

static block_t *find_prev(block_t *block)
{
    word_t *footerp = (&(block->header)) - 1;
    size_t size = get_size(*footerp);
    block_t *block_prev = (block_t *) ((char *) block - size);
    return block_prev;
}

static block_t *coalesce(block_t *block)
{
    block_t *block_next = find_next(block);
    block_t *block_prev = find_prev(block);
    bool prev_alloc = get_alloc(block_prev->header);
    bool next_alloc = get_alloc(block_next->header);
    size_t size = get_size(block->header);

    if (prev_alloc && next_alloc) {
        return block;
    } else if (!prev_alloc && next_alloc) {
        size += get_size(block_prev->header);
        write_header(block_prev, size, 0);
        write_footer(block_prev);
        block = block_prev;

        remove_block(block_prev);
//        mm_checkheap(__LINE__);
    } else if (prev_alloc && !next_alloc) {
        size += get_size(block_next->header);
        write_header(block, size, 0);
        write_footer(block);

        remove_block(block_next);
//        mm_checkheap(__LINE__);
    } else {
        size += get_size(block_next->header) + get_size(block_prev->header);
        write_header(block_prev, size, 0);
        write_footer(block_prev);
        block = block_prev;

        remove_block(block_prev);
        remove_block(block_next);

//        mm_checkheap(__LINE__);
    }
    return block;
}

static block_t *extend_heap(size_t size)
{
    void *bp;
    block_t *block, *block_next;
    size = round_up(size, ALIGNMENT);
    if ((bp = mem_sbrk(size)) == (void *) -1) {
        return NULL;
    }
    block = (block_t *) (((word_t *) bp) - 1);
    write_header(block, size, 0);
    write_footer(block);
    block_next = find_next(block);
    write_header(block_next, 0, 1);
    block = coalesce(block);
    return block;

}

static word_t pack(size_t size, bool alloc)
{
    return (size | alloc);
}

static size_t max(size_t x, size_t y)
{
    return (x > y) ? x : y;
}

static block_t *find_free_next(block_t *block)
{

    return (block_t *) block->next;
}

static block_t *find_free_prev(block_t *block)
{
    return (block_t *) block->prev;
}

static block_t *find_fit(size_t asize)
{
    find_count++;
    block_t *block;
    for (block = free_listp; block != NULL;
         block = find_free_next(block)) {
        block_count++;
        if (get_size(block->header) >= asize && !get_alloc(block->header)) {
            return block;
        }
    }
    return NULL;
}

static void place(block_t *block, size_t size)
{

    size_t bsize = get_size(block->header);
    block_t *block_next = NULL;
    if (bsize >= (MIN_BLOCK_SIZE + size)) {
        write_header(block, size, 1);
        write_footer(block);
        block_next = find_next(block);

        write_header(block_next, bsize - size, 0);
        write_footer(block_next);
        insert_block(block_next);

    } else {
        write_header(block, bsize, 1);
        write_footer(block);
    }

}

/*
 * LIFO
 */
static void insert_block(block_t *block)
{
    block->next = (void *) free_listp;
    if (free_listp) free_listp->prev = block;
    block->prev = NULL;
    free_listp = block;
}

static void remove_block(block_t *block)
{
    block_t *next = find_free_next(block);
    block_t *prev = find_free_prev(block);
    if (!prev)
        free_listp = next;
    else
        prev->next = (void *) next;

    if (next)
        next->prev = (void *) prev;

    //block->next = NULL;
    //lock->prev = NULL;
}

/*
 * mm_checkheap - There are no bugs in my code, so I don't need to check,
 *      so nah!
 */
void mm_checkheap(int verbose)
{
    (void) verbose;


    if (!heap_listp) {
        printf("NULL heap list pointer!\n");
    }

    block_t *curr = heap_listp;
    block_t *next;
    block_t *hi = mem_heap_hi();

    while ((next = find_next(curr)) + 1 < hi) {
        size_t size = get_size(curr->header);
        word_t *footerp = (word_t *) ((char *) curr + size - WSIZE);
        word_t hdr = curr->header;
        word_t ftr = *footerp;

        if (hdr != ftr) {
            printf("line %d: block %p\n Header (0x%016lX) != footer (0x%016lX)"
                           "\n",
                   verbose, curr, hdr, ftr
            );
            exit(-1);
        }
        curr = next;
    }

    /*
     * detect cycles in the free list
     */
    block_t *hare = free_listp;
    block_t *tortoise = free_listp;

    while (tortoise != NULL) {

        if (hare) hare = find_free_next(hare);
        if (hare) hare = find_free_next(hare);

        tortoise = find_free_next(tortoise);

        if (!tortoise)
            break;
        else if (hare == tortoise) {
            printf("line %d: detect cycles in the free list, hare(%p) == "
                           "tortoise(%p)\n",
                   verbose, hare, tortoise);
            exit(-1);
        }
    }

}

