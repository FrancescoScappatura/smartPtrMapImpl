#include <utility>
#include <cstddef>
#include <iostream>
#include <map>
#include <cstdlib>

#ifndef GENERIC_PTR_H
#define GENERIC_PTR_H

class generic_smart_pointer
{
    public:
    void* get() { return raw_pointer_;}
    void clear() { raw_pointer_=nullptr;}
    int use_count_shared() { return occ_shared[this->raw_pointer_];}
    int use_count_weak() { return occ_weak[this->raw_pointer_];}

    generic_smart_pointer(void* value)
    {
        raw_pointer_=value;
    }

    generic_smart_pointer(generic_smart_pointer& other)
    {
        this->raw_pointer_=other.raw_pointer_;
    };


    generic_smart_pointer(generic_smart_pointer&& other)
    {
       std::cout<<"move_constructor"<<std::endl;
       this->raw_pointer_=other.raw_pointer_;
       other.raw_pointer_=nullptr;
    }
    
    void operator=(generic_smart_pointer& other)
    {
        if (this->raw_pointer_==other.raw_pointer_) {return;}

        this->raw_pointer_=other.raw_pointer_;
    } 

    void operator=(generic_smart_pointer&& other)
    {
        if (this->raw_pointer_==other.raw_pointer_) return;
        
        this->raw_pointer_=other.raw_pointer_;
        other.raw_pointer_=nullptr;
        // counter doesn't change.
    } 

    ~generic_smart_pointer()
    {
        if (occ_shared[this->raw_pointer_]==0 && occ_unique[this->raw_pointer_]==false)
        {
          delete (int*)raw_pointer_; 
          //TBD remove this!. Just a tmp sol for avoid free void*
          // How can this be solved?
          //Using template class we loos univoquicity because it
          //will lead to multiple maps
        }
    }
    
    static std::map<void*, int> occ_shared;
    static std::map<void*, int> occ_weak;
    static std::map<void*, bool> occ_unique;

    private:
      void* raw_pointer_;
};


std::map<void*, int> generic_smart_pointer::occ_shared{};
std::map<void*, int> generic_smart_pointer::occ_weak{};
std::map<void*, bool> generic_smart_pointer::occ_unique{};

#endif