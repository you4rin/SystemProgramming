//2019027001
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include "cachelab.h"

typedef struct _entry{
    char valid;
    unsigned long long tag;
    int lasttime;
}Entry;

typedef struct _set{
    Entry* entry;
}Set;

typedef struct _cache{
    int curtime, hit, miss, evict;
    Set* set;
}Cache;

void loadorset(Cache* cache, unsigned long long row, unsigned long long tag, int E, int verbose){
    int vacant = -1, evictidx = -1, evictcnt = __INT_MAX__, flag = 0, dataidx;
    for(int i = 0; i < E; ++i){
        if(!cache->set[row].entry[i].valid){
            if(vacant == -1)
                vacant = i;
            continue;
        }
        if(cache->set[row].entry[i].tag != tag){
            if(evictcnt > cache->set[row].entry[i].lasttime){
                evictcnt = cache->set[row].entry[i].lasttime;
                evictidx = i;
            }
            continue;
        }
        flag = 1;
        dataidx = i;
        break;
    }
    if(flag){  
        if(verbose)
            printf("hit ");
        cache->hit++;
        cache->set[row].entry[dataidx].lasttime = cache->curtime++;
    }
    else{
        if(verbose)
            printf("miss ");
        cache->miss++;
        if(vacant != -1){
            cache->set[row].entry[vacant].valid = 1;
            cache->set[row].entry[vacant].tag = tag;
            cache->set[row].entry[vacant].lasttime = cache->curtime++;
        }
        else{
            if(verbose)
                printf("evict ");
            cache->evict++;
            cache->set[row].entry[evictidx].valid = 1;
            cache->set[row].entry[evictidx].tag = tag;
            cache->set[row].entry[evictidx].lasttime = cache->curtime++;
        }
    }
}

int main(int argc, char* argv[])
{
    int option = 0, s, E, b, verbose = 0, size;
    int setnum;
    unsigned long long tag, row;
    char instruction;
    char* t = NULL;
    FILE* fp;
    while((option = getopt(argc, argv, "vs:E:b:t:")) != -1){
        switch(option){
            case's':
                s = atoi(optarg);
                break;
            case'E':
                E = atoi(optarg);
                break;
            case'b':
                b = atoi(optarg);
                break;
            case'v':
                verbose = 1;
                break;
            case't':
                t = optarg;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    Cache* cache = (Cache*)malloc(sizeof(Cache));
    cache->set = (Set*)malloc(sizeof(Set) * (1 << s));
    setnum = (1 << s);
    for(int i = 0; i < setnum; ++i){
        cache->set[i].entry = (Entry*)malloc(sizeof(Entry) * E);
        for(int j = 0; j < E; ++j){
            cache->set[i].entry[j].valid = 0;
        }
    }
    cache->hit = cache->miss = cache->evict = cache->curtime = 0;

    fp = fopen(t, "r");
    while(fscanf(fp, " %c %llx,%d", &instruction, &tag, &size) == 3){
        if(instruction == 'I')
            continue;
        if(verbose)
            printf("%c %llx,%d ", instruction, tag, size);
        row = (tag >> b) & ((1 << s) - 1);
        tag >>= (s + b);
        switch(instruction){
            case 'M':
                loadorset(cache, row, tag, E, verbose);
            case 'L':
            case 'S':
                loadorset(cache, row, tag, E, verbose);
                printf("\n");
                break;
            default:
                break;
        }

    }
    printSummary(cache->hit, cache->miss, cache->evict);
    return 0;
}
