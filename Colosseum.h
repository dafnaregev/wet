//
// Created by user on 27/12/2017.
//

#ifndef WET2_COLOSSEUM_H
#define WET2_COLOSSEUM_H

#include "TrainingGroup.h"
#include "Gladiator.h"
#include "SplayTree.h"
#include "HashTable.h"
#include "MinHeap.h"

class Colosseum{
private:
    HashTable<int,TrainingGroup> trainingGroupsHT;
    MinHeap trainingGroupHeap;
    SplayTree<int,long long> allGladiators;

public:

    /*initializes hashTable and minHeap
    * Input:         n - number of groups
     *               trainingGroupIDs - IDs of the groups
    * Output:        None.
    * Return Values: None.
    */
    Colosseum(int n, int *trainingGroupsIDs) {
        Node **nodes = new Node*[n];
        this->trainingGroupHeap.MakeHeap(n, trainingGroupsIDs, nodes);
        TrainingGroup* groups = new TrainingGroup[n];
        for (int i = 0; i < n; i++) {
            TrainingGroup* temp=new TrainingGroup(trainingGroupsIDs[i]);
            (*temp).SetHeapPtr(nodes[i]);
            groups[i]=*temp;
            delete(temp);
        }
        this->trainingGroupsHT.init(n, trainingGroupsIDs, groups);
        delete[](groups);
        delete[](nodes);
    }

    /*add a training group to the system
    * Input:         trainingGroupID - ID of the new group
    * Output:        None.
    * Return Values: None.
    */
    void addTrainingGroup(int trainingGroupID) {
        if (trainingGroupID < 0) {
            throw ColosseumExceptions::InvalidInput();
        }
        TrainingGroup trainer(trainingGroupID);

        if (this->trainingGroupsHT.member(trainingGroupID) != NULL) {
            throw ColosseumExceptions::Failure();
        }
        Node *ptr = this->trainingGroupHeap.Insert(trainingGroupID);
        trainer.SetHeapPtr(ptr);
        this->trainingGroupsHT.insert(trainingGroupID, trainer);
    }

    /*add a new gladiator to the system
    * Input:         gladiatorID - ID of the new gladiator
     *               score - the score of the new gladiator
     *               trainingGroup - ID of the gladiator's group
    * Output:        None.
    * Return Values: None.
    */
    void addGladiator(int gladiatorID, int score, int trainingGroup) {
        if(gladiatorID<0 || trainingGroup<0 || score<0) {
            throw ColosseumExceptions::InvalidInput();
        }

        TrainingGroup* temp=this->trainingGroupsHT.member(trainingGroup);
        if(temp==NULL) {
            throw ColosseumExceptions::Failure();
        }

        Gladiator gladiator(gladiatorID,score);
        long long lscore=(long long)score;
        try {
            this->allGladiators.insert(gladiatorID,lscore);
        }
        catch (SplayTreeExceptions::ElementAlreadyExists) {
            throw ColosseumExceptions::Failure();
        }

        temp->insertGladiator(gladiator);
    }


    /*checks which group has lower k score and remove the losing group
     * from the heap
    * Input:         trainingGroup1 - ID of the 1st group
     *               trainingGroup2 - ID of the 2nd group
     *               k1 - number of top gladiators to check in 1st group
     *               k2 - number of top gladiators to check in 2nd group
    * Output:        None.
    * Return Values: None.
    */
    void trainingGroupFight(int trainingGroup1, int trainingGroup2, int k1, int k2) {
        if (k1 <= 0 || k2 <= 0 || trainingGroup1 < 0 || trainingGroup2<0){
            throw ColosseumExceptions::InvalidInput();
        }
        if(trainingGroup1==trainingGroup2){
            throw ColosseumExceptions::Failure();
        }
        TrainingGroup* group1=this->trainingGroupsHT.member(trainingGroup1);
        TrainingGroup* group2=this->trainingGroupsHT.member(trainingGroup2);
        if(group1==NULL || group2==NULL || group1->GetIsActive()== false || group2->GetIsActive()== false){
            throw ColosseumExceptions::Failure();
        }
        if(group1->GetNumOfGladiators()<k1 || group2->GetNumOfGladiators()<k2){
            throw ColosseumExceptions::Failure();
        }
        int score1=group1->getKTopScores(k1);
        int score2=group2->getKTopScores(k2);
        if(score1<score2){
            group1->SetActiveStatus(false);
            this->trainingGroupHeap.Delete(group1->GetHeapPtr());
        } else if(score1>score2){
            group2->SetActiveStatus(false);
            this->trainingGroupHeap.Delete(group2->GetHeapPtr());
        } else{
            if(group1->GetGroupID()<group2->GetGroupID()){
                group2->SetActiveStatus(false);
                this->trainingGroupHeap.Delete(group2->GetHeapPtr());
            } else{
                group1->SetActiveStatus(false);
                this->trainingGroupHeap.Delete(group1->GetHeapPtr());
            }
        }
    }

    /*finds the minimum active group in the system
    * Input:         trainingGroup - a pointer to the found group
    * Output:        None.
    * Return Values: None.
    */
    void getMinTrainingGroup(int *trainingGroup){
        if(trainingGroup==NULL){
            throw ColosseumExceptions::InvalidInput();
        }
        *trainingGroup=trainingGroupHeap.FindMin();
    }

    /*deletes all of the groups and gladiators of the system.
    * Input:         trainingGroup - a pointer to the found group
    *               trainingGroup2 - ID of the 2nd group
    * Output:        None.
    * Return Values: None.
    */
    ~Colosseum() {
        for(int i=0;i<trainingGroupsHT.getSize();i++) {
            for (List<NodeHash<int, TrainingGroup> >::Iterator it = trainingGroupsHT.getArray()[i].begin();
                 it != trainingGroupsHT.getArray()[i].end(); it++) {
                (*it).getData().SetHeapPtr(NULL);
                (*it).getData().getGladiators().clear();
            }
        }
        this->allGladiators.clear();
    }

};
#endif //WET2_COLOSSEUM_H