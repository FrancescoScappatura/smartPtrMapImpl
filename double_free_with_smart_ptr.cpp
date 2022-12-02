#include <memory>
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

void doubleFreeUnique()
{
    int *pointer=new int(5); 
    std::unique_ptr<int> sp1(pointer);
    std::unique_ptr<int> sp2(pointer); //double free
}

void doubleFreeUniqueMapImpl()
{
    int *pointer=new int(5); 
    unique_ptr<int> sp1(pointer);
    unique_ptr<int> sp2(pointer); //sp2 won't be initialized. 
    //TBD: what action can be taken? exception?
}

void doubleFreeSharedWrongCount()
{
    int *pointer=new int(5);  
    std::shared_ptr<int> p102(pointer);
    std::shared_ptr<int> p103(pointer);
    std::cerr<<"counter is: "<<p102.use_count();     //double free + wrong count=1
}

void doubleFreeSharedWrongCountMapImpl()
{
    int *pointer=new int(5);  
    shared_ptr<int> p102(pointer);
    shared_ptr<int> p103(pointer);
    std::cerr<<"counter is: "<<p102.use_count();  //no double free + correct count=2
}

void bindToBothUniqueAndShared()
{
    int *pointer=new int(5);  
    std::shared_ptr<int> p102(pointer);
    std::unique_ptr<int> sp2(pointer); 
    //double free + wrong count + semantically incorrect
}

void bindToBothUniqueAndSharedMapImpl()
{
    int *pointer=new int(5);  
    shared_ptr<int> p102(pointer);
    unique_ptr<int> sp2(pointer); 
    //double free + wrong count + semantically incorrect
}



int main()
{   
    /*Test 1*/
    doubleFreeUnique(); //Uses std::smart_ptr
    //doubleFreeUniqueMapImpl(); //Uses smart_ptr_with_map
    
    /*Test 2*/
    //doubleFreeSharedWrongCount();  //Uses std::smart_ptr
    //doubleFreeSharedWrongCountMapImpl();  //Uses smart_ptr_with_map
    
    /*Test 3*/
    //bindToBothUniqueAndShared(); //Uses std::smart_ptr
    //bindToBothUniqueAndSharedMapImpl();//Uses smart_ptr_with_map
    return 0;
}