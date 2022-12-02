#include "generic_ptr.hpp" 

#ifndef WEAK_PTR_H
#define WEAK_PTR_H

template <class T> 
class weak_ptr
{
    public:
    weak_ptr(T*):p{T} {generic_smart_pointer::occ_weak[p.get()]++; };
    T* get() { return p.raw_pointer_;}

    int use_count() { return p.use_count_shared();}

    weak_ptr(weak_ptr& other):this->p{other.p}
    {
        generic_smart_pointer::occ_weak[p.get()]++;
    };


    weak_ptr(weak_ptr&& other):this->p{std::move(other.p)}
    {
        //perfect forwarding?
    }
    
    void operator=(weak_ptr& other)
    {
        this->p=other.p;
        generic_smart_pointer::occ_weak[p.get()]++;
    } 

    void operator=(weak_ptr&& other)
    {
        this->p=std::move(other.p);
    } 

    ~weak_ptr()
    {
        generic_smart_pointer::occ_weak[p.get()]--;
    }

    private:
      generic_smart_pointer<T> p;
};

#endif