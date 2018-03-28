#include <iostream>
#include "MinHeap.h"

int main() {

    MinHeap heap;
    int arr[]={0,2,33,44,121,5423,3,17,5,8,4,6,12,10};
    Node* ptrs=new Node[14];
    heap.MakeHeap(14,arr,&ptrs);

    int num=100;
    heap.Insert(num);

    num=-1;
    heap.Insert(num);

    int min=heap.FindMin();
    std::cout<< min << std::endl;
    heap.DelMin();

    num=9;
    heap.Insert(num);

    for(int i=0;i<16;i++){
        min=heap.FindMin();
        std::cout<< min << std::endl;
        heap.DelMin();
    }

    MinHeap heap2;
    int arr2[]={2,0};
    Node* ptrs2=new Node[2];
    heap2.MakeHeap(2,arr2,&ptrs2);
    for(int i=100;i>2;i--){
        heap2.Insert(i);
    }
    for(int i=-5;i<0;i++){
        heap2.Insert(i);
    }
    for(int i=0;i<105;i++){
        min=heap2.FindMin();
        std::cout<< min << std::endl;
        heap2.DelMin();
    }




    return 0;
}