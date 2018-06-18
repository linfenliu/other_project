

#ifndef FL_SMART_PTR_H
#define FL_SMART_PTR_H

#include "config.h"

FL_ENTER

template<typename T>
class SmartPtr
{
public:
    SmartPtr(T* real_ptr = nullptr);
    SmartPtr(const SmartPtr& rhs);
    ~SmartPtr();
    
    SmartPtr& operator=(const SmartPtr& rhs);
    
    T* operator->() const;
    T& operator*() const;
    
    bool operator!() const;
    operator bool() const;
    
    template<typename U>
    operator SmartPtr<U>();
    
private:
    T* pointer;
};

template<typename T>
SmartPtr<T>::SmartPtr(T* real_ptr):pointer(real_ptr)
{
    if(pointer != nullptr)
    {
        pointer->IncreaseRef();
    }
}


template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& rhs):pointer(rhs.pointer)
{
    if(pointer != nullptr)
    {
        pointer->IncreaseRef();
    }
}


template<typename T>
SmartPtr<T>::~SmartPtr()
{
    if(pointer != nullptr)
    {
        pointer->DecreaseRef();
    }
}


template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& rhs)
{
    if(this == &rhs)    return *this;
    
    if(pointer != nullptr)
    {
        pointer->DecreaseRef();
    }
    
    pointer = rhs.pointer;
    
    if(pointer != nullptr)
    {
        pointer->IncreaseRef();
    }
    
    return *this;
}


template<typename T>
T* SmartPtr<T>::operator->() const
{
    return pointer;
}


template<typename T>
T& SmartPtr<T>::operator*() const
{
    return *pointer;
}


template<typename T>
bool SmartPtr<T>::operator!() const
{
    return pointer == nullptr;
}


template<typename T>
SmartPtr<T>::operator bool() const
{
    return !(operator!());
}

template<typename T>
template<typename U>
SmartPtr<T>::operator SmartPtr<U>()
{
    return SmartPtr<U>(pointer);
}

FL_LEAVE





#endif

