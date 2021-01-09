#ifndef WEAKPTR_H
#define WEAKPTR_H

template<typename>
class Sharedptr;

template<typename T>
class Weakptr
{
public:
    Weakptr()
    {
        ptr = nullptr;
    };

    Weakptr(const Weakptr<T>& _Weakptr)
    {
        ptr = _Weakptr.ptr;
        count = _Weakptr.count;
    };

    Weakptr(const Sharedptr<T>& _Sharedptr)
    {
        ptr = _Sharedptr.ptr;
        count = _Sharedptr.count;
    };

    Weakptr<T>& operator = (const Weakptr<T>& _Weakptr)
    {
        ptr = _Weakptr.ptr;
        count = _Weakptr.count;
    };

    Weakptr<T>& operator = (const Sharedptr<T>& _Sharedptr)
    {
        ptr = _Sharedptr.ptr;
        count = _Sharedptr.count;
    };

    ~Weakptr()
    {

    };

    T* ptr;
    int* count;
};

#endif