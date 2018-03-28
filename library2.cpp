#include "Colosseum.h"
#include "library2.h"

/*initializes hashTable and minHeap
* Input:         DS - the system
 *               n - number of groups
 *               trainingGroupIDs - IDs of the groups
* Output:        None.
* Return Values: NULL - if DS==NULL, if n<2 or if any trainingGroupID<0
*                Colosseum *DS - if SUCCESS.
*/
void* init(int n, int *trainingGroupsIDs) {
    if (n < 2) {
        return NULL;
    }
    for(int i=0;i<n;i++) {
        if(trainingGroupsIDs[i]<0) {
            return NULL;
        }
    }
    Colosseum *DS = new Colosseum(n, trainingGroupsIDs);
    return (void *) DS;
}

/*add a new trainingGRoup to the system
* Input:         DS - the system
 *               trainingGroupID - ID of the new group
* Output:        None.
* Return Values: INVALID_INPUT - if DS==NULL, trainingGroupID<0
*               ALLOCATION_ERROR - if there is any bad_alloc
*               FAILURE - if there is a group with this ID
*                SUCCESS - in success.
*/
StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    try {
        ((Colosseum *) DS)->addTrainingGroup(trainingGroupID);
    } catch (ColosseumExceptions::Allocation_Error) {
        return ALLOCATION_ERROR;
    } catch (ColosseumExceptions::InvalidInput) {
        return INVALID_INPUT;
    } catch (ColosseumExceptions::Failure) {
        return FAILURE;
    }
    return SUCCESS;
}

/*add a new gladiator to the system
* Input:         DS - the system
 *               gladiatorID - ID of the new gladiator
 *               score - the score of the new gladiator
 *               trainingGroup - ID of the gladiator's group
* Output:        None.
* Return Values: INVALID_INPUT - if DS==NULL, score<0
 *               ALLOCATION_ERROR - if there is any bad_alloc
 *               FAILURE - if there is no such group of if there is a gladiator with this ID
*                SUCCESS - in success.
*/
StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    try {
        ((Colosseum *) DS)->addGladiator(gladiatorID,score,trainingGroup);
    } catch (ColosseumExceptions::Allocation_Error) {
        return ALLOCATION_ERROR;
    } catch (ColosseumExceptions::InvalidInput) {
        return INVALID_INPUT;
    } catch (ColosseumExceptions::Failure) {
        return FAILURE;
    }
    return SUCCESS;
}

/*checks which group has lower k score and remove the losing group
 * from the heap
* Input:         DS - the system
 *               trainingGroup1 - ID of the 1st group
 *               trainingGroup2 - ID of the 2nd group
 *               k1 - number of top gladiators to check in 1st group
 *               k2 - number of top gladiators to check in 2nd group
* Output:        None.
* Return Values: INVALID_INPUT - if DS==NULL, k1,k2<=0
 *              FAILURE - if the groups aren't found or of the k1/k2 are too big
*                SUCCESS - in success.
*/
StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    try {
        ((Colosseum *) DS)->trainingGroupFight(trainingGroup1,trainingGroup2,k1,k2);
    } catch (ColosseumExceptions::Allocation_Error) {
        return ALLOCATION_ERROR;
    } catch (ColosseumExceptions::InvalidInput) {
        return INVALID_INPUT;
    } catch (ColosseumExceptions::Failure) {
        return FAILURE;
    }
    return SUCCESS;
}

/*finds the minimum active group in the system
* Input:         DS - the system
 *               trainingGroup - a pointer to the found group
* Output:        None.
* Return Values: INVALID_INPUT - if DS==NULL or trainingGroup==NULL.
*                SUCCESS - in success.
*/
StatusType getMinTrainingGroup(void *DS, int *trainingGroup){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    try {
        ((Colosseum *) DS)->getMinTrainingGroup(trainingGroup);
    } catch (ColosseumExceptions::Allocation_Error) {
        return ALLOCATION_ERROR;
    } catch (ColosseumExceptions::InvalidInput) {
        return INVALID_INPUT;
    } catch (ColosseumExceptions::Failure) {
        return FAILURE;
    }
    return SUCCESS;
}

/* Description:   Quits and deletes the database.
*                DS should be set to NULL.
* Input:         DS - A pointer to the data structure.
* Output:        None.
* Return Values: None.
*/
void quit(void** DS){
    if(DS==NULL){
        return;
    }
    delete (Colosseum*)(*DS);
    *DS= NULL;
}









