#include <memory>
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

void doubleFreeUnique()
{
    int *pointer=new int(5);  

    std::unique_ptr<int> sp1(pointer);
    std::unique_ptr<int> sp2(pointer);

    //double free
}

void doubleFreeSharedWrongCount()
{
    int *pointer=new int(5);  

    std::shared_ptr<int> p102(pointer);
    std::shared_ptr<int> p103(pointer);

    std::cerr<<p102.use_count();

    //double free + wrong count
}


void BindToUniqueAndShared()
{
    int *pointer=new int(5);  
    shared_ptr<int> p102(pointer);
    unique_ptr<int> sp2(pointer);
    //double free + wrong count + semantically incorrect
}


int main()
{   
    BindToUniqueAndShared();
     

    return 0;
}