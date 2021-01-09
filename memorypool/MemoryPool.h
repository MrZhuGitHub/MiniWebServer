/*****************************************************
实现固定大小分配的内存池，按照8、16、32、64、128、256的大小
维护6个空闲链表，分配内存只需要删除一个节点，释放内存需要添
加一个节点。每次分配内存，头部四个字节记录内存块的大小，方便
后续释放内存时，找到对应的链表，当内存不足时每次扩展4096个字
节的内存块。分配和释放的时间复杂度都可以保证在O（1）内完成，
但是存在内存碎片的问题。此外对内存的分配和释放过程进行了加锁，
可以保证线程的安全性。
*****************************************************/
#include<malloc.h>
#include<string.h>

#pragma pack(4)

#define chunk 4096
#define Recordblock 4
#define blocktypes 6
#define sizeofptr 8

#define block8 0
#define block16 1
#define block32 2
#define block64 3
#define block128 4
#define block256 5

void* MyMalloc(unsigned size);
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
    void* Malloc(const int& UnitType);
    void Free(void* p,  const int& UnitType);
    ~MemoryPool();

private:
    char* Head_MemoryPool[blocktypes];
    Node* Head_FreeList[blocktypes];
    Node Head_FreeMem[blocktypes];
};