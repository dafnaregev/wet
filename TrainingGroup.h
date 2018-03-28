//
// Created by user on 27/12/2017.
//

#ifndef WET2_TRAININGGROUP_H
#define WET2_TRAININGGROUP_H

#include "Gladiator.h"
#include "SplayTree.h"
#include "MinHeap.h"


class TrainingGroup{
private:
    int trainingGroupID;
    bool isActive;
    int numOfGladiators;
    SplayTree<Gladiator,long long> gladiators;
    Node* heapPtr;

public:
    TrainingGroup():trainingGroupID(0),isActive(false),numOfGladiators(0),heapPtr(NULL) {
    };
    TrainingGroup(int id):trainingGroupID(id),isActive(true),numOfGladiators(0),heapPtr(NULL){
    };

    void insertGladiator(Gladiator& gladiator) {
        try {
            long long score=gladiator.getScore();
            gladiators.insert(gladiator, score);
        }catch (SplayTreeExceptions::AllocationError){
            throw TrainerExceptions::AllocationError();
        }
        this->numOfGladiators++;
    }

    int GetNumOfGladiators(){
        return this->numOfGladiators;
    }

    void SetActiveStatus(bool isActive){
        this->isActive=isActive;
    }

    void SetHeapPtr(Node* ptr){
        this->heapPtr=ptr;
    }

    bool GetIsActive(){
        return this->isActive;
    }

    int getKTopScores(int k) {
        return this->gladiators.getSubScoreByRank(this->numOfGladiators - k);
    }

    int GetGroupID(){
        return this->trainingGroupID;
    }

    SplayTree<Gladiator,long long> getGladiators() {
        return this->gladiators;
    };

    Node* GetHeapPtr() {
        return this->heapPtr;
    }

};


#endif //WET2_TRAININGGROUP_H