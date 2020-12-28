/*****************************************************
实现固定大小分配的内存池，按照4、8、16、32、64、128的大小
维护6个空闲链表，分配内存只需要删除一个节点，释放内存需要添
加一个节点。每次分配内存，头部四个字节记录内存块的大小，方便
后续释放内存时，找到对应的链表，当内存不足时每次扩展1024个字
节的内存块。分配和释放的时间复杂度都可以保证在O（1）内完成，
但是存在内存碎片的问题。此外对内存的分配和释放过程进行了加锁，
可以保证线程的安全性。
*****************************************************/
#include<malloc.h>
#include<string.h>

#define size_4 4
#define size_8 8
#define size_16 16
#define size_32 32
#define size_64 64
#define size_128 128

void* MyMalloc(int size);
void MyFree(void* ptr);

struct Node
{
    int size;
    Node* next;
};

class MemoryPool
{
public:
    MemoryPool();
    void* Malloc(int size,  const int& UnitType);
    void Free(void* p,  const int& UnitType);
    void* ExtendMemory(const int& UnitType);
    ~MemoryPool();

    char* Head_MemoryPool[6];
    Node* Head_FreeList[6];
    Node* Head_FreeMem[6];
};