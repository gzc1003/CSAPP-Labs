#include "cachelab.h"
#include <assert.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int LRU_counter = 0;

struct cache_line {
    int valid_bit;
    int counter;
    unsigned long tag;
};

int hit(struct cache_line* cache, int set, unsigned long tag, int E);
int load(struct cache_line* cache, int set, unsigned long tag, int E);
void my_access(int* hit_n, int* miss_n, int* eviction_n,
    struct cache_line* cache, int set, int tag, int E);
int get_set(unsigned long addr, int s, int b);
unsigned long get_tag(unsigned long addr, int s, int b);
int power2(int n);

int main(int argc, char* argv[])
{
    int s, E, b;
    struct cache_line* cache;
    int hit_n = 0, miss_n = 0, eviction_n = 0;
    int set;
    unsigned long tag;

    FILE* fp;
    char access_type;
    unsigned long addr;
    int size;

    char opt;
    char* file_path = NULL;

    while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (opt) {
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            file_path = optarg;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    if (optind == 1) {
        printf("Need options\n");
        abort();
    }

    cache
        = (struct cache_line*)calloc(power2(s) * E, sizeof(struct cache_line));
    assert(cache != NULL);

    fp = fopen(file_path, "r");
    assert(fp != NULL);

    while (fscanf(fp, " %1c %16lx,%2d", &access_type, &addr, &size) > 0) {
        // if (access_type != 'I')
        //    printf("%c %lx,%d ", access_type, addr, size);

        set = get_set(addr, s, b);
        tag = get_tag(addr, s, b);

        if (access_type == 'L' || access_type == 'S') {
            my_access(&hit_n, &miss_n, &eviction_n, cache, set, tag, E);
        } else if (access_type == 'M') {
            my_access(&hit_n, &miss_n, &eviction_n, cache, set, tag, E);
            my_access(&hit_n, &miss_n, &eviction_n, cache, set, tag, E);
        }

        // if (access_type != 'I')
        //    printf("\n");
    }

    fclose(fp);
    free(cache);

    printf("hit:%d miss:%d eviction:%d\n", hit_n, miss_n, eviction_n);
    printSummary(hit_n, miss_n, eviction_n);
    return 0;
}

void my_access(int* hit_n, int* miss_n, int* eviction_n,
    struct cache_line* cache, int set, int tag, int E)
{
    int tmp = 0;
    if (hit(cache, set, tag, E)) {
        (*hit_n)++;
        // printf("hit ");
    } else {
        (*miss_n)++;
        // printf("miss ");
        tmp += load(cache, set, tag, E);
        *eviction_n += tmp;
        // if (tmp)
        //    printf("eviction ");
    }
}

int power2(int n)
{
    int i, res = 1;
    for (i = 0; i < n; i++)
        res *= 2;
    return res;
}

int hit(struct cache_line* cache, int set, unsigned long tag, int E)
{
    struct cache_line* cache_set = cache + set * E;
    int res = 0;
    int i;
    for (i = 0; i < E; i++) {
        if (cache_set[i].valid_bit && cache_set[i].tag == tag) {
            res = 1;
            cache_set[i].counter = LRU_counter;
            LRU_counter++;
            break;
        }
    }
    return res;
}

int load(struct cache_line* cache, int set, unsigned long tag, int E)
{
    struct cache_line* cache_set = cache + set * E;
    int eviction = 1;
    int i;
    int min_counter = cache_set->counter, index = 0;
    for (i = 0; i < E; i++) {
        if (!cache_set[i].valid_bit) {
            index = i;
            eviction = 0;
            break;
        }

        if (cache_set[i].counter < min_counter) {
            min_counter = cache_set[i].counter;
            index = i;
        }
    }

    cache_set[index].tag = tag;
    cache_set[index].valid_bit = 1;
    cache_set[index].counter = LRU_counter;
    LRU_counter++;

    return eviction;
}

int get_set(unsigned long addr, int s, int b)
{
    int res;
    unsigned long mask = 0;
    int i;
    int tmp = 1;
    for (i = 0; i < s; i++) {
        tmp *= 2;
    }
    mask = tmp - 1;
    addr >>= b;
    res = addr & mask;
    return res;
}

unsigned long get_tag(unsigned long addr, int s, int b)
{
    addr >>= s + b;
    return addr;
}
