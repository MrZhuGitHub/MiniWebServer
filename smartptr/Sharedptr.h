#ifndef SHAREDPTR_H
#define SHAREDPTR_H

template<typename T>
class Weakptr;

template<typename T>
class Sharedptr
{
public:
    Sharedptr(T* _ptr = nullptr):ptr(_ptr)
    {
        count = new int(1);
    };

    Sharedptr(const Sharedptr<T>& _Sharedptr)
    {
        ptr = _Sharedptr.ptr;
        count = _Sharedptr.count;
        (*count)++;
    };

    Sharedptr(const Weakptr<T>& _Weakptr)
    {
        if(_Weakptr.ptr != this->ptr)
        {
            ptr = _Weakptr.ptr;
            count = _Weakptr.count;
            (*count)++;
        }
    };

    Sharedptr<T>& operator = (const Sharedptr<T>& _Sharedptr)
    {
        if(_Sharedptr.ptr != this->ptr)
        {
            if((*count) == 1)
            {
                delete count;
                if(ptr != nullptr)
                    delete ptr;
                ptr = _Sharedptr.ptr;
                count = _Sharedptr.count;
                (*count)++;
            }
            else
            {                    
                ptr = _Sharedptr.ptr;
                (*count)--;
                count = _Sharedptr.count;
                (*count)++;
            }
        }
        return *this;
    };

    Sharedptr<T>& operator = (const Weakptr<T>& _Weakptr)
    {
        if(_Weakptr.ptr != this->ptr)
        {
            if((*count) == 1)
            {
                delete count;
                if(ptr != nullptr)
                    delete ptr;
                ptr = _Weakptr.ptr;
                count = _Weakptr.count;
                (*count)++;
            }
            else
            {                    
                ptr = _Weakptr.ptr;
                (*count)--;
                count = _Weakptr.count;
                (*count)++;
            }
        }
        return *this;
    };

    T* operator -> ()
    {
        return ptr;
    };

    T operator * ()
    {
        return *ptr;
    };

    ~Sharedptr()
    {
        if((*count) == 1)
        {
            delete count;
            if(ptr != nullptr)
                delete ptr;
        }
        else
        {
            (*count)--;
        }
    };

    T* ptr;
    int* count;
};

#endif