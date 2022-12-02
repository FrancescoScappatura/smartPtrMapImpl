#include "generic_ptr.hpp" 

#ifndef SHARED_PTR_H
#define SHARED_PTR_H
template <class T> 
class shared_ptr
{
    public:
    shared_ptr(T* par):p{par} {generic_smart_pointer::occ_shared[p.get()]++; };
    T* get() { return p.raw_pointer_;}

    int use_count() { return p.use_count_shared();}

    shared_ptr(shared_ptr& other):p{other.p}
    {
        generic_smart_pointer::occ_shared[p.get()]++;
    };

    shared_ptr(shared_ptr&& other):p{std::move(other.p)}
    {
        //perfect forwarding?
    }
    
    void operator=(shared_ptr& other)
    {
        this->p=other.p;
        generic_smart_pointer::occ_shared[p.get()]++;
    } 

    void operator=(shared_ptr&& other)
    {
        this->p=std::move(other.p);
    } 

    ~shared_ptr()
    {
        generic_smart_pointer::occ_shared[p.get()]--;
    }

    private:
      generic_smart_pointer p;
};


#endif