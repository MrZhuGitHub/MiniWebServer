#include"MemoryPool.h"

#define chunk 1024
#define block 4

static MemoryPool MemPool;

/*****************************************************
@入参：实际申请内存的大小
@出参：内存池分配内存块的类型
@说明：
*****************************************************/
int GetType(int size)
{
    if(size<=2)
    {
        return -1;      
    }
    else
    {
        return GetType(size/2)+1;
    }   
}

/*****************************************************
@入参：实际申请内存的大小
@出参：返回申请内存的指针
@说明：对于大于128字节的内存申请采用malloc()
*****************************************************/
void* MyMalloc(int size)
{
    int UnitType;
    int MemBlockSize[6] = {size_4, size_8, size_16, size_32, size_64, size_128};
    if(size > size_128)
    {
        int* p = (int*)malloc(size+block);
        *p = size;
        return p+1;
    }
    else if (size<=2)
    {
        UnitType = GetType(size+2);
    }
    else
    {
        UnitType = GetType(size);
    }
    return MemPool.Malloc(MemBlockSize[UnitType], UnitType);
}

/*****************************************************
@入参：释放指针指向的内存
@出参：
@说明：头部4个字节记录内存的大小
*****************************************************/
void MyFree(void* ptr)
{
    int* size = (int*)((char*)ptr - block);
    if((*size) > 128)
    {
        free(size);
    }
    else
    {
        MemPool.Free(ptr, GetType(*size));
    }
}

/*****************************************************
@入参：
@出参：
@说明：初始化6个1024字节的内存块，每个分别按照4、8、16、32、64、128的固定大小分配内存
*****************************************************/
MemoryPool::MemoryPool()
{
    for(int i=0; i<6 ;i++)
    {
        Head_MemoryPool[i] = (char*)malloc(chunk);
        if(Head_MemoryPool[i] == NULL)
        {
            printf("MemoryPool initial failed!\n");
            return;
        }
        Head_FreeList[i] = NULL;
        Head_FreeMem[i] = (Node*)Head_MemoryPool;
        Head_FreeMem[i]->size = chunk;
        Head_FreeMem[i]->next = NULL;
    }
}

/*****************************************************
@入参：申请内存块的类型
@出参：
@说明：向内存池申请指定大小内存，如果内存不足则扩展内存
*****************************************************/
void* MemoryPool::Malloc(int size, const int& UnitType)
{
    Node* Mem;
    int MemLen = size + block;
    if(Head_FreeList == NULL)
    {
        int capacity = Head_FreeMem[UnitType]->size - 2*block;
        if(capacity < MemLen)
        {
            ExtendMemory(UnitType);
        }
        Mem = Head_FreeMem[UnitType];
        Head_FreeMem[UnitType]->size = Head_FreeMem[UnitType]->size - MemLen ;
        memcpy((char*)Head_FreeMem[UnitType] + MemLen, (char*)Head_FreeMem[UnitType], (2*block));
        Head_FreeMem[UnitType] = (Node*)((char*)Head_FreeMem[UnitType] + MemLen);
        Mem->size = size;
        return &(Mem->next);       
    }
    Head_FreeList[UnitType] = Head_FreeList[UnitType]->next;
    return &(Head_FreeList[UnitType]->next);
}

/*****************************************************
@入参：内存块的类型
@出参：
@说明：扩展1024字节的内存
*****************************************************/
void* MemoryPool::ExtendMemory(const int& UnitType)
{
    int offset = Head_FreeMem[UnitType]->size - block;
    char** NextChunk;
    NextChunk = (char**)((char*)Head_FreeMem[UnitType] + offset);
    *NextChunk = (char*)malloc(chunk);
    if(*NextChunk == NULL)
    {
        printf("Get NextChunk failed!\n");
        return NULL; 
    }
    memcpy(*NextChunk, Head_FreeMem[UnitType], 8);
    Head_FreeMem[UnitType]->size = chunk;
}

/*****************************************************
@入参：
@出参：
@说明：向Head_FreeList指向的栈链表添加一个节点
*****************************************************/
void MemoryPool::Free(void* ptr, const int& UnitType)
{
    Node* p = (Node*)((char*)ptr - block);
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
