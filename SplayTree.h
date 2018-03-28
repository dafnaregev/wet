#include <iostream>
#include "Exception.h"
#include "assert.h"

#ifndef WET_1_SPLAYTREE_H
#define WET_1_SPLAYTREE_H

template <class T,class S>
class SplayTree {
    class Node {
    private:
        T key;
        S data;
        long int rank;
        long long sumSub;
        Node* lson;
        Node* rson;
        Node *father;
    public:
        //Constructor of the Node
        //Parameters: Key and Data
        Node(const T& key, const S& data) : key(key), data(data), lson(
                NULL), rson(NULL), father(NULL) {
        }

        //Copy Constructor of the Node
        Node(const Node& node) {
            this->key=node.key;
            this->data=node.data;
            this->lson=node.lson;
            this->rson=node.rson;
            this->father=node.father;
        }

        friend class SplayTree;
    };

private:
    Node* root;

    //Finding Node in the tree according to the key
    Node* finding(Node* root, T& key) {
        Node* ptr= root;
        while(ptr != NULL) {
            if(key < ptr->key) {
                ptr=ptr->lson;
            }
            else if(key > ptr->key) {
                ptr=ptr->rson;
            }
            else {
                return ptr;
            }
        }
        return NULL;
    }

    //Zig Rotation
    void zig(Node* ptr,Node* father) {
        father->lson=ptr->rson;

        if(ptr->rson != NULL) {
            ptr->rson->father=father;
        }
        ptr->rson=father;
        father->father=ptr;
        ptr->father= NULL;

        //Update the father
        father->rank = 1;
        father->sumSub = father->data;
        if(father->lson != NULL) {
            father->rank += father->lson->rank;
            father->sumSub += father->lson->sumSub;
        }
        if(father->rson != NULL) {
            father->rank += father->rson->rank;
            father->sumSub += father->rson->sumSub;
        }
        //

        //Update the son
        ptr->rank = 1;
        ptr->sumSub = ptr->data;
        if(ptr->lson != NULL) {
            ptr->rank += ptr->lson->rank;
            ptr->sumSub += ptr->lson->sumSub;
        }
        if(father != NULL) {
            ptr->rank += father->rank;
            ptr->sumSub += father->sumSub;
        }
        //
    }

    //Zag Rotation
    void zag(Node* ptr,Node* father) {
        father->rson=ptr->lson;

        if(ptr->lson != NULL) {
            ptr->lson->father=father;
        }
        ptr->lson=father;
        father->father=ptr;
        ptr->father= NULL;

        //Update father
        father->rank = 1;
        father->sumSub = father->data;
        if(father->lson != NULL) {
            father->rank += father->lson->rank;
            father->sumSub += father->lson->sumSub;
        }
        if(father->rson != NULL) {
            father->rank += father->rson->rank;
            father->sumSub += father->rson->sumSub;
        }
        //

        //Update son
        ptr->rank = 1;
        ptr->sumSub = ptr->data;
        if(father != NULL) {
            ptr->rank += father->rank;
            ptr->sumSub += father->sumSub;
        }
        if(ptr->rson != NULL) {
            ptr->rank += ptr->rson->rank;
            ptr->sumSub += ptr->rson->sumSub;
        }
        //
    }

    //Zig-Zig Rotation
    void zigZig(Node* ptr,Node* father, T key) {
        Node* grand_father=father->father;
        father->lson=ptr->rson;
        if(ptr->rson != NULL) {
            ptr->rson->father=father;
        }
        grand_father->lson=father->rson;
        if(father->rson != NULL) {
            father->rson->father=grand_father;
        }
        ptr->father=grand_father->father;
        if(grand_father->father != NULL) {
            if(grand_father->father->lson != NULL && grand_father->father->lson->key == grand_father->key) {
                grand_father->father->lson=ptr;
            }
            else if(grand_father->father->rson != NULL && grand_father->father->rson->key == grand_father->key) {
                grand_father->father->rson=ptr;
            }
        }
        ptr->rson=father;
        father->rson=grand_father;
        father->father=ptr;
        grand_father->father=father;


        //Update grand-father
        grand_father->rank=1;
        grand_father->sumSub=grand_father->data;
        if(grand_father->lson != NULL) {
            grand_father->rank += grand_father->lson->rank;
            grand_father->sumSub += grand_father->lson->sumSub;
        }
        if(grand_father->rson != NULL) {
            grand_father->rank += grand_father->rson->rank;
            grand_father->sumSub += grand_father->rson->sumSub;
        }
        //Update father
        father->rank=1;
        father->sumSub=father->data;
        if(father->lson != NULL) {
            father->rank += father->lson->rank;
            father->sumSub += father->lson->sumSub;
        }
        if(grand_father!=NULL) {
            father->rank += grand_father->rank;
            father->sumSub += grand_father->sumSub;
        }

        //Update son
        ptr->rank=1;
        ptr->sumSub=ptr->data;
        if(ptr->lson != NULL) {
            ptr->rank += ptr->lson->rank;
            ptr->sumSub += ptr->lson->sumSub;
        }
        if(father != NULL) {
            ptr->rank += father->rank;
            ptr->sumSub += father->sumSub;
        }
    }

    //Zig-Zag Rotation
    void zigZag(Node* ptr,Node* father, T key) {
        Node* grand_father=father->father;
        father->rson=ptr->lson;
        if(ptr->lson != NULL) {
            ptr->lson->father=father;
        }

        grand_father->lson=ptr->rson;
        if(ptr->rson != NULL) {
            ptr->rson->father=grand_father;
        }
        ptr->father=grand_father->father;
        if(grand_father->father != NULL) {
            if(grand_father->father->lson != NULL && grand_father->father->lson->key == grand_father->key) {
                grand_father->father->lson=ptr;
            }
            else if(grand_father->father->rson != NULL && grand_father->father->rson->key == grand_father->key) {
                grand_father->father->rson=ptr;
            }
        }
        father->father=ptr;
        ptr->lson=father;
        ptr->rson=grand_father;
        grand_father->father=ptr;

        //Update grand-father
        grand_father->rank=1;
        grand_father->sumSub=grand_father->data;
        if(grand_father->lson != NULL) {
            grand_father->rank += grand_father->lson->rank;
            grand_father->sumSub += grand_father->lson->sumSub;
        }
        if(grand_father->rson != NULL) {
            grand_father->rank += grand_father->rson->rank;
            grand_father->sumSub += grand_father->rson->sumSub;
        }
        //Update father
        father->rank=1;
        father->sumSub=father->data;
        if(father->lson != NULL) {
            father->rank += father->lson->rank;
            father->sumSub += father->lson->sumSub;
        }
        if(father->rson != NULL) {
            father->rank += father->rson->rank;
            father->sumSub += father->rson->sumSub;
        }
        //Update son
        ptr->rank=1;
        ptr->sumSub=ptr->data;
        if(father != NULL) {
            ptr->rank += father->rank;
            ptr->sumSub += father->sumSub;
        }
        if(grand_father != NULL) {
            ptr->rank += grand_father->rank;
            ptr->sumSub += grand_father->sumSub;
        }
    }

    //Zag-Zag Rotation
    void zagZag(Node* ptr,Node* father, T key) {
        Node* grand_father=father->father;
        father->rson=ptr->lson;
        if(ptr->lson != NULL) {
            ptr->lson->father=father;
        }
        grand_father->rson=father->lson;
        if(father->lson != NULL) {
            father->lson->father=grand_father;
        }
        ptr->father=grand_father->father;
        if(grand_father->father != NULL) {
            if(grand_father->father->rson != NULL && grand_father->father->rson->key == grand_father->key) {
                grand_father->father->rson=ptr;
            }
            else if(grand_father->father->lson != NULL && grand_father->father->lson->key == grand_father->key) {
                grand_father->father->lson=ptr;
            }
        }
        ptr->lson=father;
        father->lson=grand_father;
        father->father=ptr;
        grand_father->father=father;

        //Update grand-father
        grand_father->rank=1;
        grand_father->sumSub=grand_father->data;
        if(grand_father->lson != NULL) {
            grand_father->rank += grand_father->lson->rank;
            grand_father->sumSub += grand_father->lson->sumSub;
        }
        if(grand_father->rson != NULL) {
            grand_father->rank += grand_father->rson->rank;
            grand_father->sumSub += grand_father->rson->sumSub;
        }
        //Update father
        father->rank=1;
        father->sumSub=father->data;
        if(grand_father != NULL) {
            father->rank += grand_father->rank;
            father->sumSub += grand_father->sumSub;
        }
        if(father->rson != NULL) {
            father->rank += father->rson->rank;
            father->sumSub += father->rson->sumSub;
        }
        //Update son
        ptr->rank=1;
        ptr->sumSub=ptr->data;
        if(father != NULL) {
            ptr->rank += father->rank;
            ptr->sumSub += father->sumSub;
        }
        if(ptr->rson != NULL) {
            ptr->rank += ptr->rson->rank;
            ptr->sumSub += ptr->rson->sumSub;
        }
    }

    //Zag-Zig Rotation
    void zagZig(Node* ptr,Node* father, T key) {
        Node* grand_father=father->father;
        father->lson=ptr->rson;
        if(ptr->rson != NULL) {
            ptr->rson->father=father;
        }

        grand_father->rson=ptr->lson;
        if(ptr->lson != NULL) {
            ptr->lson->father=grand_father;
        }
        ptr->father=grand_father->father;
        if(grand_father->father != NULL) {
            if(grand_father->father->lson != NULL && grand_father->father->lson->key == grand_father->key) {
                grand_father->father->lson=ptr;
            }
            else if(grand_father->father->rson != NULL && grand_father->father->rson->key == grand_father->key) {
                grand_father->father->rson=ptr;
            }
        }
        father->father=ptr;
        ptr->rson=father;
        ptr->lson=grand_father;
        grand_father->father=ptr;

        //Update grand-father
        grand_father->rank=1;
        grand_father->sumSub=grand_father->data;
        if(grand_father->lson != NULL) {
            grand_father->rank += grand_father->lson->rank;
            grand_father->sumSub += grand_father->lson->sumSub;
        }
        if(grand_father->rson != NULL) {
            grand_father->rank += grand_father->rson->rank;
            grand_father->sumSub += grand_father->rson->sumSub;
        }
        //Update father
        father->rank=1;
        father->sumSub=father->data;
        if(father->lson != NULL) {
            father->rank += father->lson->rank;
            father->sumSub += father->lson->sumSub;
        }
        if(father->rson != NULL) {
            father->rank += father->rson->rank;
            father->sumSub += father->rson->sumSub;
        }
        //Update Son
        ptr->rank=1;
        ptr->sumSub=ptr->data;
        if(grand_father != NULL) {
            ptr->rank += grand_father->rank;
            ptr->sumSub += grand_father->sumSub;
        }
        if(father != NULL) {
            ptr->rank += father->rank;
            ptr->sumSub += father->sumSub;
        }
    }

    //The function applying Rotations to bring the Node with the Key to the
    // root of the tree
    //Parameters: The root of the tree, and the Key of the Node that we want
    // to bring to the root
    Node* arrange(Node* root, T& key) {
        Node* ptr= finding(root, key);
        if(ptr == NULL) {
            return root;
        }
        while(1) {
            if(ptr->father == NULL) { //should be for assertation
                break;
            }
            Node* father=ptr->father;
            if(father->father == NULL) { //Then we are in Zig/Zag mode
                if(father->lson != NULL && father->lson->key == key) { //Zig mode
                    zig(ptr,father);
                }
                else if(father->rson != NULL && father->rson->key == key) { //Zag mode
                    zag(ptr,father);
                }
                else { //WE SHOULD NEVER GET HERE
                    return NULL;
                }
            }
            else if(father->father->lson != NULL && ptr->father->key == father->father->lson->key) { //Then we are in Zig-Zag/Zig-Zig mode
                if(father->lson != NULL && father->lson->key == ptr->key) { //Zig-Zig mode
                    zigZig(ptr,father,key);
                }
                else if(father->rson != NULL && father->rson->key == ptr->key) { //Zig-Zag mode
                    zigZag(ptr,father,key);
                }

                else {  //WE SHOULD NEVER GET HERE
                    return NULL;
                }
            }
            else if(father->father->rson != NULL && ptr->father->key == father->father->rson->key) { //Then we are in Zag-Zag/Zag-Zig mode
                if(father->rson != NULL && father->rson->key == ptr->key) {  //Zag-Zag mode
                    zagZag(ptr,father,key);
                }
                else if(father->lson != NULL && father->lson->key == ptr->key) { //Zag-Zig
                    zagZig(ptr,father,key);
                }
                else { //WE SHOULD NEVER GET HERE
                    return NULL;
                }
            }
        }
        return ptr;
    }

    //The function
    void join() {
        if(this->root == NULL) {
            return;
        }
        if(this->root->lson== NULL && this->root->rson== NULL){
            delete this->root;
            this->root= NULL;
            return;
        }
        if(this->root->lson == NULL) {
            Node* to_delete=this->root;
            this->root=this->root->rson;
            delete to_delete;
            this->root->father= NULL;
        }
        else if(this->root->rson == NULL) {
            Node* to_delete=this->root;
            this->root=this->root->lson;
            delete to_delete;
            this->root->father= NULL;
        }
        else {
            Node* ptr=this->root->lson;
            while(ptr->rson != NULL) {
                ptr=ptr->rson;
            }
            ptr->rson=this->root->rson;
            ptr->rson->father=ptr;
            if(ptr != this->root->lson) {
                if(ptr->father!= NULL && ptr->lson!= NULL) {
                    ptr->father->rson = ptr->lson;
                    ptr->lson->father = ptr->father;
                }
                ptr->lson=root->lson;
                ptr->lson->father=ptr;
            }
            Node* to_delete=this->root;
            this->root=ptr;
            if(ptr->father->rson==ptr){
                ptr->father->rson= NULL;
            }
            delete to_delete;
            this->root->father= NULL;
        }
    }

    //Return the Number of Nodes in the tree
    int getNumOfSons(Node* root) {
        int count = 0;
        if (root == NULL) {
            return count;
        }
        return getNumOfSons(root->lson)+getNumOfSons(root->rson)+1;
    }

    template<class Func>
    void inOrderHelper(Node* root, Func& func) {
        if(root == NULL) {
            return;
        }
        inOrderHelper(root->lson,func);
        func(root->data);
        inOrderHelper(root->rson,func);
    }

    template<class Func>
    void inOrderRightHelper(Node* root, Func& func) {
        if(root == NULL) {
            return;
        }
        inOrderRightHelper(root->rson,func);
        func(root->data);
        inOrderRightHelper(root->lson,func);
    }

    int getSubScoreByRankAux(int k,Node* root,int sumOfScore)
    {
        if(root==NULL){ //if the index doesnt exist
            return -1;
        }

        if(root->lson==NULL && root->rson==NULL && root->rank==k) {
            return sumOfScore;
        }
        if(root->lson!=NULL && root->lson->rank==k-1){
            return sumOfScore - root->lson->sumSub;
        }
        if(root->lson!=NULL && root->lson->rank>k-1){
            return getSubScoreByRankAux(k,root->lson,sumOfScore);
        }
        if(root->lson!=NULL && root->lson->rank<k-1){
            return getSubScoreByRankAux(k-root->lson->rank-1,root->rson,sumOfScore-root->lson->sumSub-root->data);
        }
        if(root->lson == NULL && k == 1) {
            return sumOfScore;
        }
        return getSubScoreByRankAux(k-1,root->rson,sumOfScore-root->data);
    }

    Node* select(int k,Node* root) {
        if (root == NULL || k<=0) { //if the index doesnt exist
            return NULL;
        }
        int rleft = root->lson ? root->lson->rank : 0;

        if (rleft == k - 1) {
            return root;
        } else if (rleft > k - 1) {
            return select(k, root->lson);
        } else if (rleft < k - 1) {
            return select(k - rleft - 1, root->rson);
        }

        return NULL;

    }


public:
    //Constructor of the Tree
    SplayTree() {
        this->root= NULL;
    }

    //The function applying "in order" scan and apply the func function on
    // each node in the tree
    template<class Func>
    void inOrder(Func& func) {
        inOrderHelper(this->root,func);
    }

    //The function applying "in order" scan in the opposite form and apply
    // the func function on each node in the tree
    template<class Func>
    void inOrderRight(Func& func) {
        inOrderRightHelper(this->root,func);
    }

    // Find and Return the Node with the Key
    // The function bring the Node that addede to the root, if The Node doesnt
    // found we bring to the root the last Node in the searching path
    //Parameters: the Key of the Node that we want to find
    //Exceptions: SplayTreeExceptions::ElementNotFound if the element doesnt exist
    S& find(T& key) {
        Node* ptr= root;
        while(ptr != NULL) {
            if(key < ptr->key) {
                if(ptr->lson== NULL){
                    this->root=arrange(this->root,ptr->key);
                    ptr= NULL;
                } else {
                    ptr = ptr->lson;
                }
            }
            else if(key > ptr->key) {
                if(ptr->rson== NULL){
                    this->root=arrange(this->root,ptr->key);
                    ptr= NULL;
                } else {
                    ptr = ptr->rson;
                }
            }
            else {
                this->root=arrange(this->root,key);
                return ptr->data;
            }
        }
        throw SplayTreeExceptions::ElementNotFound();
    }

    //Find and return the minimum Node in the tree
    //Exceptions: SplayTreeExceptions::EmptyTree if the Tree is empty
    S& findMin(){
        Node* ptr=this->root;
        if(ptr== NULL){
            throw SplayTreeExceptions::EmptyTree();
        }
        while (ptr->lson!= NULL){
            ptr=ptr->lson;
        }
        this->root=arrange(this->root,ptr->key);
        return ptr->data;
    }

    //Find and return the maximum Node in the tree
    //Exceptions: SplayTreeExceptions::EmptyTree if the Tree is empty
    S& findMax(){
        Node* ptr=this->root;
        if(ptr== NULL){
            throw SplayTreeExceptions::EmptyTree();
        }
        while (ptr->rson!= NULL){
            ptr=ptr->rson;
        }
        this->root=arrange(this->root,ptr->key);
        return ptr->data;
    }

    //Insert a Node to the tree
    //Parameters: Key of the Node and it's Data
    //Exceptions: SplayTreeExceptions::AllocationError() if bad allocation occurred
    //            SplayTreeExceptions::ElementAlreadyExists() if the Node Alreay Exists
    void insert(T& key, S& data) {
        try {
            find(key);
        }
        catch(SplayTreeExceptions::ElementNotFound) {
            Node* element;
            try{
                element=new Node(key, data);
            }catch (std::bad_alloc){
                throw SplayTreeExceptions::AllocationError();
            }
            Node* ptr=this->root;
            element->rank=1;
            element->sumSub=element->data;
            if(ptr == NULL) {
                this->root=element;
                return;
            }

            while(ptr->lson != NULL || ptr->rson != NULL) {
                if(key< ptr->key) {
                    if(ptr->lson != NULL) {
                        ptr=ptr->lson;
                    }
                    else {
                        break;
                    }
                }
                else if(key > ptr->key) {
                    if(ptr->rson != NULL) {
                        ptr=ptr->rson;
                    }
                    else {
                        break;
                    }
                }
            }
            if(key < ptr->key) {
                ptr->lson=element;
                ptr->lson->father=ptr;
            }
            else {
                ptr->rson=element;
                ptr->rson->father=ptr;
            }

            Node* temp = element->father;
            while(temp != NULL) {
                temp->rank+=1;
                temp->sumSub+=element->data;
                temp=temp->father;
            }

            this->root=arrange(this->root,key);
            return;
        }
        throw SplayTreeExceptions::ElementAlreadyExists();
    }

    void insertAny(T& key, const S& data) {
        /*
        try {
            find(key);
        }
        catch(SplayTreeExceptions::ElementNotFound) {;}*/
        Node* element;
        try{
            element=new Node(key, data);
        }catch (std::bad_alloc){
            throw SplayTreeExceptions::AllocationError();
        }
        Node* ptr=this->root;
        element->rank=1;
        element->sumSub=element->key;
        if(ptr == NULL) {
            this->root=element;
            return;
        }

        while(ptr->lson != NULL || ptr->rson != NULL) {
            if(key< ptr->key) {
                if(ptr->lson != NULL) {
                    ptr=ptr->lson;
                }
                else {
                    break;
                }
            }
            else if(key >= ptr->key) {
                if(ptr->rson != NULL) {
                    ptr=ptr->rson;
                }
                else {
                    break;
                }
            }
        }
        if(key < ptr->key) {
            ptr->lson=element;
            ptr->lson->father=ptr;
        }
        else {
            ptr->rson=element;
            ptr->rson->father=ptr;
        }

        Node* temp = element->father;
        while(temp != NULL) {
            temp->rank+=1;
            temp->sumSub+=element->key;
            temp=temp->father;
        }

        this->root=arrange(this->root,key);
    }

    //Removing a Node in the tree according to the Key that provided
    //Parameters: The Key of the Node
    //Exceptions: SplayTreeExceptions::ElementNotFound() if Node with the
    //            provided Key doesnt exist
    void remove(T& key) {
        try{
            find(key);
        }
        catch(SplayTreeExceptions::ElementNotFound) {
            throw SplayTreeExceptions::ElementNotFound();
        }
        join();
    }

    //Printing the tree
    void printTree() {
        if(this->root== NULL){
            return;
        }
        std::cout << "Root:" << this->root->key << std::endl;
        inOrder(this->root);
        std::cout << std::endl;
    }

    //Return the Size of the tree
    int getSize() {
        return getNumOfSons(this->root);
    }

    //The function get a sored array, and return a tree in form of lanyard
    //Parameters: sorted array, the size of the array
    //Exceptions: SplayTreeExceptions::AllocationError if bad allocation occurred
    void createLanyard(T* array, int index) {
        int i=0;
        Node* element;
        try{
            element=new Node(array[0],array[i]);
        }
        catch (std::bad_alloc) {
            throw SplayTreeExceptions::AllocationError();
        }
        this->root=element;
        i++;
        Node* lastElement=element;
        while(i< index) {
            try {
                element = new Node(array[i], array[i]);
            } catch (std::bad_alloc) {
                throw SplayTreeExceptions::AllocationError();
            }
            lastElement->rson=element;
            element->father=lastElement;

            lastElement=element;
            i++;
        }
    }

    //Clear the tree
    //Parameters: The root of the tree
    void clear(Node *root) {
        if (root == NULL) {
            return;
        }
        clear(root->lson);
        clear(root->rson);
        delete (root);
    }

    //Clear the tree
    void clear(){
        clear(this->root);
    }

    //Destructor of the Tree
    ~SplayTree() {
        //clear(this->root);
    }


    Node* sortedArrayToTreeAux(T* array,Node* father, int start, int end) {
        if(start > end) {
            return NULL;
        }

        int mid = (start + end) / 2;
        Node *root;
        try {
            root = new Node(array[mid], array[mid]);
        }catch (std::bad_alloc){
            throw ColosseumExceptions::Allocation_Error();
        }
        if(father != NULL) {
            root->father=father;
        }

        root->lson=sortedArrayToTreeAux(array,root,start,mid-1);
        root->rson=sortedArrayToTreeAux(array,root,mid+1,end);

        return root;
    }

    void sortedArrayToTree(T* array,int length) {
        this->root=sortedArrayToTreeAux(array,NULL,0,length-1);
    }

    int getSubScoreByRank(int k){
        Node* node=select(k+1,this->root);
        find(node->key);
        if(node->rson){
            return node->rson->sumSub+node->data;
        }
        return node->data;
    }




};


#endif //WET_1_SPLAYTREE_H
