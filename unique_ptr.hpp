#include "generic_ptr.hpp" 

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <class T> 
class unique_ptr
{
    public:
    unique_ptr(T* par): p{par}
    {
      if ((generic_smart_pointer::occ_unique.count(p.get())>0 &&
           generic_smart_pointer::occ_unique[p.get()]==true)  ||
           generic_smart_pointer::occ_shared[p.get()]>0
           )
      {
        //memory location already assigned to another up
        std::cout<<"unique_ptr_violation"<<std::endl;
        p.clear();
        return;
      }

      generic_smart_pointer::occ_unique[p.get()]=true; 
    };

    T* get() { return p.raw_pointer_;}

    unique_ptr(unique_ptr& other)=delete;


    unique_ptr(unique_ptr&& other):p{std::move(other.p)}
    {
        //perfect forwarding?
    }
    
    void operator=(unique_ptr& other) = delete;

    void operator=(unique_ptr&& other)
    {
        this->p=std::move(other.p);
    } 

    ~unique_ptr()
    {
        generic_smart_pointer::occ_unique[p.get()]=false;
    }

    private:
      generic_smart_pointer p;
};

#endif