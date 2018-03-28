//
// Created by yahav on 27/12/2017.
//
#include "List.h"
#include "Exception.h"

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

template <class T,class S>
class NodeHash {
private:
    T key;
    S data;
public:

    //Constructor of the Node
    //Parameters: Key and Data
    NodeHash(const T& key, const S& data) : key(key), data(data) {
    }

    //Copy Constructor of the Node
    NodeHash(const NodeHash<T,S>& node) {
        this->key=node.key;
        this->data=node.data;
    }

    T& getKey() {
        return this->key;
    }
    S& getData() {
        return this->data;
    }


};


template <class T,class S>
class HashTable {

private:
    List<NodeHash<T,S> >* hash;
    long int size;
    long int numOfElements;


public:
    HashTable():size(0),numOfElements(0){};
/*
    HashTable(int n,T* input,S default_data) {
        this->size=n;
        this->numOfElements=n;
        this->hash=new List<NodeHash<T,S> >[n];
        for(int i=0;i<n;i++) {
            NodeHash<T,S>* node=new NodeHash<T,S>(input[i],default_data);
            hash[input[i]%n].insert(*node);
            delete(node);
        }
    }
*/
    void init(int n,T* input,S* data) {
        this->size = n;
        this->numOfElements = n;
        this->hash = new List<NodeHash<T, S> >[n];
        for (int i = 0; i < n; i++) {
            NodeHash<T,S> node(input[i], data[i]);
         //   NodeHash<T, S> *node = new NodeHash<T, S>(input[i], data[i]);
            hash[input[i] % n].insert(node);
           // delete (node);
        }
    }

    void insert(T& key,S& data) {
        /*
        if (member(key)!=NULL) {
            throw HashExceptions::AlreadyExists();
        }*/
        this->numOfElements++;
        NodeHash<T,S> node(key,data);
        if(this->numOfElements >= size) {
            List<NodeHash<T,S> >* temp = new List<NodeHash<T,S> >[2*size];
            for(int i=0;i<size;i++) {
                for(typename List<NodeHash<T,S> >::Iterator it = hash[i].begin(); it != hash[i].end(); it++) {
                    T temp_key=(*it).getKey();
                    temp[temp_key%(size*2)].insert(*it);
                }
            }
            delete[] this->hash;
            this->hash=temp;
            size*=2;
        }
        hash[key%size].insert(node);
    }

    S* member(T& key) {
        for(typename List<NodeHash<T,S> >::Iterator it = hash[key%size].begin(); it != hash[key%size].end(); it++) {
            if((*it).getKey() == key) {
                return &((*it).getData());
            }
        }
        return NULL;
    }

    int getSize(){
        return this->size;
    }

    List<NodeHash<T,S> >* getArray() {
        return this->hash;
    };

    ~HashTable(){
        delete[](this->hash);
    }
};

#endif //WET2_HASHTABLE_H