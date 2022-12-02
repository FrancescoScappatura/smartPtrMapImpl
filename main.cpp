#include "shared_ptr.hpp" 
#include "unique_ptr.hpp"

int main()
{   
    
    int *pointer=new int(5);  
    shared_ptr<int> p(pointer);
    std::cout<<p.use_count()<<std::endl;
    shared_ptr<int> p100(pointer);
    std::cout<<p.use_count()<<std::endl;
    shared_ptr<int> p101(std::move(p100));
    std::cout<<p.use_count()<<std::endl;

    unique_ptr<int> p102(pointer);
    unique_ptr<int> p103(pointer);
    unique_ptr<int> p104(std::move(p102));

    return 0;
}