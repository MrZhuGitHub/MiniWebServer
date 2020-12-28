#include"MemoryPool.h"
#include<time.h>
#include<iostream>

int main()
{
    time_t Membegin, Memend, begin, end;
    int* all[1000000];
    //内存池统计分配时间
    Membegin = time((time_t*)NULL);
    for(int i=0; i<1000000; i++)
    {
        all[i] = (int*)MyMalloc(sizeof(int));
    }
    for(int i=0; i<1000000; i++)
    {
        MyFree(all[i]);
    }
    Memend = time((time_t*)NULL);
    printf("MemoryPool consume %d seconds\n",Memend-Membegin);
    //malloc和free统计分配时间
    begin = time((time_t*)NULL);
    for(int i=0; i<1000000; i++)
    {
        all[i] = (int*)malloc(sizeof(int));
    }
    for(int i=0; i<1000000; i++)
    {
        free(all[i]);
    }
    end = time((time_t*)NULL);
    printf("malloc&free consume %d seconds\n",end-begin);
}