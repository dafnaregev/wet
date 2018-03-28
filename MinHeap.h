//
// Created by user on 27/12/2017.
//

#ifndef WET2_MINHEAP_H
#define WET2_MINHEAP_H

#include "assert.h"
#include <iostream>
#include "Exception.h"


class Node {
public:
    int key;
    Node* lson;
    Node* rson;
    Node *father;

    //Constructor of the Node
    //Parameters: Key and Data
    Node(int key) : key(key),lson(NULL), rson(NULL), father(NULL) {
    }

    Node():key(0),lson(NULL), rson(NULL), father(NULL){}

    //Copy Constructor of the Node
    Node(Node& node) {
        this->key=node.key;
        this->lson=node.lson;
        this->rson=node.rson;
        this->father=node.father;
    }

    //Assignment operator of the Node
    Node& operator=(const Node& node) {
        if(this==&node){
            return *this;
        }
        this->key=node.key;
        this->lson=node.lson;
        this->rson=node.rson;
        this->father=node.father;
        return *this;
    }

    int getKey(){
        return this->key;
    }
};

class MinHeap {
private:
    Node *root;
    int numOfElements;

    void Swap(Node* node,Node* father){
        Node *tmp = father;
        Node *tmp_f = NULL;
        if (this->root == father) {
            this->root = node;
        } else {
            tmp_f = father->father;
        }
        if (node == father->lson) {
            Node *tmp_r = father->rson;
            if (node->lson != NULL) {
                father->lson = node->lson;
                father->lson->father=father;
            } else {
                father->lson = NULL;
            }
            if (node->rson != NULL) {
                father->rson = node->rson;
                father->rson->father=father;
            } else {
                father->rson = NULL;
            }
            if(tmp_r!=NULL) {
                node->rson = tmp_r;
                node->rson->father = node;
            } else{
                node->rson=NULL;
            }
            node->lson = tmp;
            node->lson->father = node;
        } else {
            Node *tmp = father;
            Node *tmp_l = father->lson;
            if (node->lson != NULL) {
                father->lson = node->lson;
                father->lson->father=father;
            } else {
                father->lson = NULL;
            }
            if (node->rson != NULL) {
                father->rson = node->rson;
                father->rson->father=father;
            } else {
                father->rson = NULL;
            }
            if(tmp_l!=NULL) {
                node->lson = tmp_l;
                node->lson->father = node;
            } else{
                node->lson=NULL;
            }
            node->rson = tmp;
            node->rson->father = node;
        }
        if (tmp_f != NULL && tmp_f->lson!=NULL && father==tmp_f->lson) {
            tmp_f->lson = node;
            node->father=tmp_f;
        } else if (tmp_f != NULL && tmp_f->rson!=NULL && father==tmp_f->rson) {
            tmp_f->rson = node;
            node->father=tmp_f;
        } else {
            node->father = NULL;
        }
    }
    void SiftUp(Node *node) {
        while (node != NULL && node->father != NULL && node->key < node->father->key) {
            Swap(node,node->father);
        }
    }

    void SiftDown(Node* node) {
        while (node != NULL) {
            if (node->rson != NULL && node->lson != NULL) {
                if (node->key > node->lson->key && node->lson->key <= node->rson->key) {
                    Swap(node->lson,node);
                } else if (node->key > node->rson->key && node->rson->key < node->lson->key) {
                    Swap(node->rson,node);
                } else if (node->key < node->lson->key && node->key > node->rson->key) {
                    Swap(node->rson,node);
                } else if (node->key < node->rson->key && node->key > node->lson->key) {
                    Swap(node->lson,node);
                } else {
                    return;
                }
            } else if (node->rson != NULL && node->key > node->rson->key) {
                Swap(node->rson,node);
            } else if (node->lson != NULL && node->key > node->lson->key) {
                Swap(node->lson,node);
            } else {
                return;
            }
        }
    }

    long long getSizeOfIndex(int num) {
        long long count=0;
        int tmp=num;
        while (tmp!=0){
            tmp=tmp/2;
            count++;
        }

        return count;
    }

    Node* FindElementFather(int index){
        if(index>this->numOfElements+1){
            return NULL;
        }
        long long size=getSizeOfIndex(index);
        int* arr=new int[size];
        int i=size-1;
        while (index != 0) {
            int reminder = index % 2;
            if(reminder==0) {
                arr[i--]=0;
            } else{
                arr[i--]=1;
            }
            index = index / 2;
        }
        i=1;
        Node* tmp=this->root;
        while (i<size-1) {
            if (arr[i]==0) {
                tmp = tmp->lson;
            } else {
                tmp = tmp->rson;
            }
           i++;
        }
        delete[] arr;
        return tmp;
    }

    Node* FindElement(int index){
        if(index>this->numOfElements){
            return NULL;
        }
        long long size=getSizeOfIndex(index);
        int* arr=new int[size];
        int i=size-1;
        while (index != 0) {
            int reminder = index % 2;
            if(reminder==0) {
                arr[i--]=0;
            } else{
                arr[i--]=1;
            }
            index = index / 2;
        }
        i=1;
        Node* tmp=this->root;
        while (i<size) {
            if (arr[i]==0) {
                tmp = tmp->lson;
            } else {
                tmp = tmp->rson;
            }
            i++;
        }
        delete[] arr;
        return tmp;
    }

    Node* createFullTree_Aux(int n,Node** ptrs,int index,int* keys,Node* root,Node* prev) {
        if(index < n) {
            Node* temp;
            try {
                temp=new Node(keys[index]);
                ptrs[index]=temp;
            }catch (std::bad_alloc){
                throw HeapExceptions::Allocation_Error();
            }
            root=temp;
            root->father=prev;
            if(index == 0) {
                root->father=NULL;
                root->lson=createFullTree_Aux(n,ptrs,2*index+1,keys,root->lson,root);
                root->rson=createFullTree_Aux(n,ptrs,2*index+2,keys,root->rson,root);
            }
            else {
                root->lson=createFullTree_Aux(n,ptrs,2*index+1,keys,root->lson,root);
                root->rson=createFullTree_Aux(n,ptrs,2*index+2,keys,root->rson,root);
            }
        }
        this->numOfElements=n;
        return root;
    }

    Node* CreateFullTree(int n,Node** ptrs,int* keys) {
        try {
            this->root = createFullTree_Aux(n,ptrs, 0, keys, NULL, NULL);
            PostOrder(this->root);
            return root;
        } catch (HeapExceptions::Allocation_Error) {
            throw HeapExceptions::Allocation_Error();
        }
    }

    void PostOrder(Node* root) {
        if(root == NULL) {
            return;
        }
        PostOrder(root->lson);
        PostOrder(root->rson);
        SiftDown(root);
    }

public:
    MinHeap() {
        this->root = NULL;
        this->numOfElements=0;
    }

    Node* MakeHeap(int n, int* keys,Node** ptrs){
        try {
            CreateFullTree(n,ptrs, keys);
        }catch (HeapExceptions::Allocation_Error){
            throw HeapExceptions::Allocation_Error();
        }
        return this->root;
    }

    Node* Insert(int key){
        Node *element;
        try {
            element = new Node(key);
        }catch (std::bad_alloc){
            throw HeapExceptions::Allocation_Error();
        }
        Node* tmp=FindElementFather(this->numOfElements+1);
        assert(tmp!=NULL);
        if(tmp->lson!=NULL){
            tmp->rson=element;
            element->father=tmp;
        } else{
            tmp->lson=element;
            element->father=tmp;
        }
        this->numOfElements++;
        SiftUp(element);
        return element;
    }

    int FindMin(){
        return this->root->key;
    }

    void DecKey(Node* p,int x){
        if(p==NULL){
            throw HeapExceptions::InvalidInput();
        }
        if(p->key<x){
            return;
        }
        p->key=x;
        SiftUp(p);
    }

    void DelMin(){
        if(this->root==NULL){
            return;;
        }
        if(this->numOfElements>1) {
            Node *tmp = this->root;
            Node *tmp_r = this->root->rson;
            Node *tmp_l = this->root->lson;
            Node *newRoot = FindElement(this->numOfElements);
            // assert(newRoot!=NULL);
            Node *father = newRoot->father;
            if (tmp_r == newRoot) {
                this->root = newRoot;
                newRoot->lson = tmp_l;
                newRoot->lson->father=newRoot;
                newRoot->rson = NULL;
                delete (father);
            } else if(tmp_l==newRoot){
                this->root=newRoot;
                newRoot->rson=NULL;
                newRoot->lson=NULL;
                delete (father);
            } else {
                if (tmp_r != NULL) {
                    newRoot->rson = tmp_r;
                    newRoot->rson->father = newRoot;
                } else {
                    newRoot->rson = NULL;
                }
                if (tmp_l != NULL) {
                    newRoot->lson = tmp_l;
                    newRoot->lson->father = newRoot;
                } else {
                    newRoot->lson = NULL;
                }
                if (father->rson != NULL) {
                    father->rson = NULL;
                } else {
                    father->lson = NULL;
                }
                delete (tmp);
            }
            this->root = newRoot;
            this->root->father=NULL;
            this->numOfElements--;
            SiftDown(this->root);

        } else{
            delete(this->root);
            this->root=NULL;
            this->numOfElements=0;
        }
    }


    void Delete(Node* p){
        if(p==this->root){
            DelMin();
        } else{
            int min=FindMin();
            DecKey(p,min-1);
            DelMin();
        }
    }

    void clear(Node *root) {
        if (root == NULL) {
            return;
        }
        clear(root->lson);
        clear(root->rson);
        delete (root);
    }

    ~MinHeap() {
        clear(this->root);
    }


};


#endif //WET2_MINHEAP_H