#include"MemoryPool.h"
#include <assert.h>
#include <iostream>

const int MemBlockSize[blocktypes] = {8, 16, 32, 64, 128, 256};
static MemoryPool MemPool;

/*****************************************************
@入参：实际申请内存的大小
@出参：返回申请内存的指针
@说明：对于大于MemBlockSize[block256]字节的内存申请采用malloc()
*****************************************************/
void* MyMalloc(unsigned int size)
{
    int UnitType;
    if(size > MemBlockSize[block256])
    {
        int* p = (int*)mmap(NULL, size + Recordblock, PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANON, 0, 0);
        *p = size;
        return p+1;
    }
    for(UnitType = block8; UnitType < blocktypes ; UnitType++)
    {
        if(UnitType == block8)
        {
            if(size <= MemBlockSize[UnitType])
                break;
        }
        else
        {
            if((MemBlockSize[UnitType-1] < size) && (size <= MemBlockSize[UnitType]))
                break;
        }
    }
    return MemPool.Malloc(UnitType);
}

/*****************************************************
@入参：释放指针指向的内存
@出参：
@说明：头部Recordblock记录内存的大小
*****************************************************/
void MyFree(void* ptr)
{
    int* size = (int*)((char*)ptr - Recordblock);
    if((*size) > MemBlockSize[block256])
    {
        munmap(((char*)ptr-Recordblock),(*size));
    }
    else
    {
        int UnitType;
        for(UnitType = block8; UnitType < blocktypes ; UnitType++)
        {
            if(UnitType == block8)
            {
                if((*size) <= MemBlockSize[UnitType])
                    break;
            }
            else
            {
                if((MemBlockSize[UnitType-1] < (*size)) && ((*size) <= MemBlockSize[UnitType]))
                    break;
            }
        }
        MemPool.Free(ptr, UnitType);
    }
}

/*****************************************************
@入参：
@出参：
@说明：初始化blocktypes个chunk字节的内存块，分别按照8、16、32、64、128、256的固定大小分配内存
*****************************************************/
MemoryPool::MemoryPool()
{
    for(int i=0; i<blocktypes ;i++)
    {
        Head_MemoryPool[i] = (char*)malloc(chunk);
        if(Head_MemoryPool[i] == NULL)
        {
            printf("MemoryPool initial failed!\n");
            assert(Head_MemoryPool[i]);
        }
        Head_FreeList[i] = NULL;
        Head_FreeMem[i].size = chunk;
        Head_FreeMem[i].next = (Node*)Head_MemoryPool[i];
    }
}

/*****************************************************
@入参：申请内存块的类型
@出参：
@说明：向内存池申请指定大小内存
*****************************************************/
void* MemoryPool::Malloc(const int& UnitType)
{
    //检查空闲链表是否为空
    if(Head_FreeList[UnitType] != NULL)
    {
        Head_FreeList[UnitType] = Head_FreeList[UnitType]->next;
        return &(Head_FreeList[UnitType]->next);      
    }
    else
    {
        Node* Mem;
        int MemLen = MemBlockSize[UnitType] + Recordblock;
        int capacity = Head_FreeMem[UnitType].size - sizeofptr;
        //如果内存块空间不足，则申请新的内存块
        if(capacity < MemLen)
        {
            char** nextchunk = (char**)((char*)Head_FreeMem[UnitType].next + capacity);
            (*nextchunk) = (char*)mmap(NULL, chunk, PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANON, 0, 0);
            if((*nextchunk) == NULL)
            {
                printf("Get NextChunk failed!\n");
                assert(*nextchunk); 
            }
            Head_FreeMem[UnitType].next = (Node*)(*nextchunk);
            Head_FreeMem[UnitType].size = chunk;
        }
        Mem = Head_FreeMem[UnitType].next;
        Head_FreeMem[UnitType].size = Head_FreeMem[UnitType].size - MemLen ;
        Head_FreeMem[UnitType].next = (Node*)((char*)Head_FreeMem[UnitType].next + MemLen);
        Mem->size = MemBlockSize[UnitType];
        return &(Mem->next); 
    }
}

/*****************************************************
@入参：
@出参：
@说明：向Head_FreeList指向的栈链表添加一个节点
*****************************************************/
void MemoryPool::Free(void* ptr, const int& UnitType)
{
    Node* p = (Node*)((char*)ptr - Recordblock);
    p->next = Head_FreeList[UnitType];
    Head_FreeList[UnitType] = p;
}

/*****************************************************
@入参：
@出参：
@说明：
*****************************************************/
MemoryPool::~MemoryPool()
{

}
