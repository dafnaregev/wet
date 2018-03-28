#include <iostream>
#include "HashTable.h"

int main() {
    int arr[]={11,11,13};
    HashTable<int,int> ht(3,arr,0);
    ht.insert(1,1);
    ht.insert(1,1);
    ht.insert(1,1);
    std::cout<<"size:" << ht.getSize()<<std::endl;
    ht.insert(3,1);
    std::cout<<"size:" <<ht.getSize()<<std::endl;
    ht.insert(1,1);
    std::cout<<"size:" <<ht.getSize()<<std::endl;

    std::cout<<"in hash:"<<std::endl;
    std::cout<<ht.member(11)<<std::endl;
    std::cout<<ht.member(1)<<std::endl;
    std::cout<<ht.member(13)<<std::endl;
    std::cout<<ht.member(3)<<std::endl;
    std::cout<<"not in hash:"<<std::endl;
    std::cout<<ht.member(111)<<std::endl;
    std::cout<<ht.member(111)<<std::endl;
    std::cout<<ht.member(113)<<std::endl;
    std::cout<<ht.member(103)<<std::endl;

    return 0;
}