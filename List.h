//
// Created by yahav on 22/06/2017.
//

#ifndef HW4_B_LIST_H
#define HW4_B_LIST_H

#include "Exception.h"



template <class T>
class List {
public:

    class Node {
    private:
        T *data;
        Node *previous;
        Node *next;
        friend class List;
        friend class Iterator;

    public:
        /* Constructor for node in the list
         * @param: the data of the node
        */
        Node(T data) {
            this->data=new T(data);
            next= NULL;
            previous= NULL;
        }
        /* Default Constructor for node
         * @param: none
        */
        Node() {
            next= NULL;
            previous= NULL;
            data= NULL;
        }

        // Destructor of the node
        ~Node() {
            delete data;
        }
    };



    class Iterator {
    private:
        Node *position;
        List *list;
        friend class List;
        friend class Node;
        /*Constructor of the Iterator
         * @param: the list of the iterator
        */
        Iterator(List *list) : list(list) {
            position= NULL;
        }

    public:

        //Copy Constructor of the Iterator
        Iterator(const Iterator& itr) {
            this->position=itr.position;
            this->list=itr.list;
        }

        //Destructor of the Iterator
        ~Iterator() {
            this->list=NULL;
            this->position=NULL;
        }

        //Dereferencing operator
        T& operator*() const {
            if(this->position == NULL) {
                throw ListExceptions::ElementNotFound();
            }
            return *(this->position->data);
        }

        //Assignment operator
        Iterator& operator=(const Iterator& itr) {
            if(this == &itr) {
                return *this;
            }

            this->position=itr.position;
            this->list=itr.list;

            return *this;
        }

        // ++Itrerator
        Iterator& operator++(){
            if (this->position->next == NULL){
                *this= this->list->end();
                return *this;
            }
            position = position->next;
            return *this;
        }

        // Itrerator++
        Iterator operator++(int){
            Iterator result(this->list);
            result=*this;
            ++(*this);
            return result;
        }

        // --Itrerator
        Iterator& operator--(){
            if(this->position == NULL) {
                Node* temp;
                temp=list->begin().position;
                if(temp == list->end().position) {
                    this->position=list->end().position;
                    return *this;
                }
                while(temp->next != NULL) {
                    temp=temp->next;
                }
                this->position=temp;
                return *this;
            }

            if (this->position->previous == NULL){
                *this=this->list->end();
                return *this;
            }

            position = position->previous;
            return *this;
        }

        // Itrerator--
        Iterator operator--(int){
            Iterator result(this->list);
            result=*this;
            --*this;
            return result;
        }

        // Comparison operator
        bool operator==(const Iterator& itr) const {
            return (this->position == itr.position && (this->list == itr.list));
        }

        // Not Comparison operator
        bool operator!=(const Iterator& itr) const {
            return !(*this == itr);
        }
    };





private:
    Node *head;

public:
    /* Constructor of the list
     * Create a empty node that will use as demo node of the list
    */
    List() {
        this->head=new Node();
    }

    //Copy Constructor of the list
    List(const List& list) {
        this->head=new Node();

        Node* ptr1=this->head;
        Node* ptr2=list.head->next;
        Node* previous=this->head;

        while(ptr2!= NULL) {
            Node* node=new Node(*(ptr2->data));
            node->previous=previous;
            if(node->previous==this->head) {
                node->previous= NULL;
            }
            ptr1->next=node;

            ptr1=ptr1->next;
            ptr2=ptr2->next;
            previous=previous->next;
        }
    }

    //Destructor of the list
    ~List(){
        Node *current = this->head->next;
        Node *next;
        while (current!=NULL){
            next = current->next;
            delete current;
            current = next;
            this->head->next = current;
        }
        delete this->head;
    }

    // Assignment operator of the list
    List& operator=(const List& list) {
        if(this == &list) {
            return *this;
        }


        Node *current = this->head->next;
        Node *next;
        while (current!=NULL){
            next = current->next;
            delete current;
            current = next;
            this->head->next = current;
        }

        Node* ptr1=this->head;
        Node* ptr2=list.head->next;
        Node* previous=this->head;

        while(ptr2!= NULL) {
            Node* node=new Node(*(ptr2->data));
            node->previous=previous;
            if(node->previous==this->head) {
                node->previous= NULL;
            }
            ptr1->next=node;

            ptr1=ptr1->next;
            ptr2=ptr2->next;
            previous=previous->next;
        }

        return *this;
    }

    //The function get the iterator to the beginning
    Iterator begin() {
        Iterator itr(this);
        if (this->head->next == NULL) {
            itr.position = NULL;
            return itr;
        }
        itr.position = this->head->next;
        return itr;
    }

    //The function get the iterator to the end
    Iterator end() {
        Iterator itr(this);
        return itr;
    }

    /* Insert node at before the iterator
     * @param: data - the data that should be added to the list
     * @param: iterator -
     * Exceptions: ElementNotFound if the element didn't find in the list
     *                             of if the iterator belong to another list
     */
    void insert(const T& data, Iterator iterator) {
        if(iterator.list != this) {
            throw ListExceptions::ElementNotFound();
        }

        if(iterator.position==NULL) {
            insert(data);
            return;
        }

        Node* node=new Node(data);

        if(this->head->next==NULL) {
            this->head->next=node;
            return;
        }

        Node* nxt=this->head;
        while(nxt->next!=iterator.position) {
            nxt=nxt->next;
        }
        node->next=nxt->next;
        if(iterator.position->previous != NULL) {
            node->previous=nxt;
        }
        nxt->next->previous=node;
        nxt->next=node;
    }

    //insert an element to the start of the list
    void insert(const T& data){
        Node* node=new Node(data);
        if(!head->next){
            this->head->next=node;
            node->previous=this->head->next;
            node->next=NULL;
        } else {
            node->next = head->next;
            head->next->previous=node;
            node->previous=head;
            head->next=node;

        }

        /*
        Node* previous=this->head->next;

        if(previous== NULL) {
            this->head->next=node;
            return;
        }

        while(previous->next != NULL) {
            previous=previous->next;
        }
        previous->next=node;
        node->previous=previous;*/
    }


    /* Remove element from the list
     * @param: iterator - the iterator that point to the node that should be removed
     * Exceptions: ElementNotFound if the element didn't find in the list
     */
    void remove(Iterator iterator){
        if (iterator.list != this || this->head->next == NULL ||
            iterator.position == NULL){
            throw ListExceptions::ElementNotFound();
        }

        Node *current = this->head;
        while (current != iterator.position && current->next!= NULL){
            current = current->next;
        }

        if (current!=iterator.position && current->next == NULL){
            throw ListExceptions::ElementNotFound();
        }

        if(current->previous == NULL && current->next == NULL) {
            head->next= NULL;
            delete current;
            return;;
        }

        if(current->previous == NULL && current->next != NULL) {
            current->next->previous= NULL;
            this->head->next=current->next;
            delete current;
            return;
        }

        Node* temp = current->next;
        Node* temp2=current->previous;
        if (temp == NULL){
            temp2->next= NULL;
            current->previous = NULL;
            iterator.position= NULL;
            delete current;
            return;
        }
        temp2->next = temp; //iterator.position->next ;
        temp->previous=temp2;
        delete current;
        iterator.position= NULL;
    }


    /* Find an element in the list
     * @param: predicate - the function using to determine if element is found
     * if the element didn't find the iterator will point to the end of the list
     */
    template<typename Predicate>
    Iterator find(const Predicate& predicate) {
        Node* ptr=this->head->next;
        Iterator itr(this);

        while(ptr != NULL) {
            if(predicate(*(ptr->data))) {
                itr.position=ptr;
                return itr;
            }
            ptr=ptr->next;
        }

        itr.position=NULL;
        return itr;
    }

    /* list sort
     * @param: compare - using to determine wheather element is biggere than another
     */
    template<typename Compare>
    void sort(const Compare& compare) {
        if(this->head->next==NULL || this->head->next->next==NULL) {
            return;
        }

        int length=this->getSize();
        Node* outPtr=this->head->next;
        Node* inPtr=this->head->next;
        Node* maxNode=this->head->next;
        bool firstRun=true;

        for(int i=0;i<length;i++) {
            inPtr=outPtr;
            if(firstRun) {
                firstRun=false;
            } else {
                outPtr=outPtr->next;
            }

            maxNode=outPtr;

            while(inPtr->next!=NULL) {
                inPtr=inPtr->next;
                if(compare(*(maxNode->data),*(inPtr->data)) == 0) {
                    maxNode=inPtr;
                }
            }

            if(outPtr!=maxNode) {
                swapNodes(*this,outPtr,maxNode);
            }
        }
    }
    void swapNodes(List list, Node* n1, Node* n2) {
        T temp=*(n1->data);
        *(n1->data)=*(n2->data);
        *(n2->data)=temp;
    }


    // Return the size of the list
    int getSize(){
        Node *current = this->head->next;
        int size =0;
        while (current != NULL){
            current = current->next;
            size++;
        }
        return size;
    }

    /* Comparison operator
     * Two lists are equal if there elements are the same
     */
    bool operator==(const List &list) const {
        Node *current1 = this->head->next;
        Node *current2 = list.head->next;

        while (current1 != NULL && current2 != NULL){
            if (*(current1->data) != *(current2->data)){
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }

        if (current1 == NULL && current2 == NULL){
            return true;
        }
        return  false;
    }

    // Not equal operator
    bool operator!=(const List &list) const {

        return !(*this == list);
    }

    bool isEmpty(){
        return this->head->next==NULL;
    }

};

#endif //HW4_B_LIST_H
