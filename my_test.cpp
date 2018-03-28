#include "library2.h"
#include "iostream"
#include "stdio.h"

#define ASSERT(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed at %s:%d %s\n",__FILE__,__LINE__,#b); \
                return false; \
        } \
} while (0)

bool InitTest(){
    int* arr=new int[3];
    arr[0]=2;
    arr[1]=-3;
    arr[2]=4;
    void* DS=init(0,arr);
    ASSERT(!DS);
    DS=init(3,arr);
    ASSERT(!DS);
    delete[] (arr);
    return true;
}

bool addTrainingGroupTest(void* DS){
    int min=0;
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==2);
    ASSERT(addTrainingGroup(NULL,1)==INVALID_INPUT);
    ASSERT(addTrainingGroup(DS,-3)==INVALID_INPUT);
    ASSERT(addTrainingGroup(DS,4)==FAILURE);
    ASSERT(addTrainingGroup(DS,2)==FAILURE);
    ASSERT(addTrainingGroup(DS,3)==FAILURE);
    ASSERT(addTrainingGroup(DS,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==1);
    return true;
}

bool addGladiatorTest(void* DS){
    ASSERT(addGladiator(NULL,100,10,1)==INVALID_INPUT);
    ASSERT(addGladiator(DS,-100,10,1)==INVALID_INPUT);
    ASSERT(addGladiator(DS,100,-10,1)==INVALID_INPUT);
    ASSERT(addGladiator(DS,100,10,-1)==INVALID_INPUT);

    ASSERT(addGladiator(DS,301,10,5)==FAILURE);

    ASSERT(addGladiator(DS,101,30,1)==SUCCESS);
    ASSERT(addGladiator(DS,102,10,1)==SUCCESS);
    ASSERT(addGladiator(DS,103,10,1)==SUCCESS);

    ASSERT(addGladiator(DS,101,10,1)==FAILURE);
    ASSERT(addGladiator(DS,102,10,1)==FAILURE);
    ASSERT(addGladiator(DS,103,10,1)==FAILURE);

    ASSERT(addGladiator(DS,201,20,2)==SUCCESS);
    ASSERT(addGladiator(DS,202,20,2)==SUCCESS);
    ASSERT(addGladiator(DS,203,20,2)==SUCCESS);

    ASSERT(addGladiator(DS,201,20,2)==FAILURE);
    ASSERT(addGladiator(DS,202,20,2)==FAILURE);
    ASSERT(addGladiator(DS,203,20,2)==FAILURE);

    ASSERT(addGladiator(DS,301,30,3)==SUCCESS);
    ASSERT(addGladiator(DS,302,30,3)==SUCCESS);
    ASSERT(addGladiator(DS,303,30,3)==SUCCESS);

    ASSERT(addGladiator(DS,401,30,4)==SUCCESS);
    ASSERT(addGladiator(DS,402,30,4)==SUCCESS);
    ASSERT(addGladiator(DS,403,30,4)==SUCCESS);
    return true;
}

bool trainingGroupFightTest(void* DS){
    int min=0;
    ASSERT(trainingGroupFight(NULL,1,2,1,1)==INVALID_INPUT);
    ASSERT(trainingGroupFight(DS,-1,2,1,1)==INVALID_INPUT);
    ASSERT(trainingGroupFight(DS,1,-2,1,1)==INVALID_INPUT);
    ASSERT(trainingGroupFight(DS,1,2,0,1)==INVALID_INPUT);

    ASSERT(trainingGroupFight(DS,1,2,5,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,5,2,1,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,1,1,1,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,1,2,1,5)==FAILURE);

    ASSERT(trainingGroupFight(DS,1,2,1,1)==SUCCESS);//group 1 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==1);

    ASSERT(trainingGroupFight(DS,1,2,1,1)==FAILURE);//group 2 can't fight
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==1);

    ASSERT(trainingGroupFight(DS,3,1,3,3)==SUCCESS);//group 3 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);

    ASSERT(trainingGroupFight(DS,1,4,1,1)==FAILURE);//group 1 can't fight

    ASSERT(trainingGroupFight(DS,3,4,3,3)==SUCCESS);//group 3 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);

    ASSERT(trainingGroupFight(DS,1,4,1,1)==FAILURE);//group 4 can't fight
    ASSERT(addGladiator(DS,404,30,4)==SUCCESS);
    ASSERT(addTrainingGroup(DS,4)==FAILURE);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);
    return true;
}

bool getMinGroupTest(void* DS){
    int min=0;
    ASSERT(getMinTrainingGroup(NULL,&min)==INVALID_INPUT);
    ASSERT(getMinTrainingGroup(DS,NULL)==INVALID_INPUT);
    return true;
}

bool advancedTest1(void* DS){
    int min=0;
    ASSERT(addTrainingGroup(DS,5)==SUCCESS);
    ASSERT(addGladiator(DS,501,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,502,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,503,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,504,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,505,20,5)==SUCCESS);
    ASSERT(addGladiator(DS,506,1000,5)==SUCCESS);

    ASSERT(addTrainingGroup(DS,6)==SUCCESS);
    ASSERT(addGladiator(DS,601,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,602,300,6)==SUCCESS);
    ASSERT(addGladiator(DS,603,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,604,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,605,20,6)==SUCCESS);
    ASSERT(addGladiator(DS,606,20,6)==SUCCESS);

    ASSERT(addTrainingGroup(DS,7)==SUCCESS);
    ASSERT(addGladiator(DS,701,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,702,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,703,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,704,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,705,20,7)==SUCCESS);
    ASSERT(addGladiator(DS,706,20,7)==SUCCESS);

    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==3);

    ASSERT(trainingGroupFight(DS,4,5,1,1)==FAILURE);//group 4 can't fight
    ASSERT(trainingGroupFight(DS,5,7,10,1)==FAILURE);
    ASSERT(trainingGroupFight(DS,5,7,3,6)==SUCCESS);//group 5 is winning
    ASSERT(trainingGroupFight(DS,5,3,1,1)==SUCCESS);//group 5 is winning

    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==5);

    ASSERT(trainingGroupFight(DS,5,6,1,1)==SUCCESS);//group 5 is winning
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==5);

    ASSERT(addTrainingGroup(DS,8)==SUCCESS);
    ASSERT(trainingGroupFight(DS,5,8,1,1)==FAILURE);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==5);

    ASSERT(addTrainingGroup(DS,0)==SUCCESS);
    ASSERT(addGladiator(DS,1234,1000,0)==SUCCESS);
    ASSERT(trainingGroupFight(DS,5,0,1,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==0);

    ASSERT(trainingGroupFight(DS,0,5,1,1)==FAILURE);//group 5 can't fight

    return true;
}

bool advancedTest2(void* DS){
    int min=0;
    ASSERT(addTrainingGroup(DS,9)==SUCCESS);
    ASSERT(addTrainingGroup(DS,10)==SUCCESS);
    ASSERT(addTrainingGroup(DS,11)==SUCCESS);
    ASSERT(addTrainingGroup(DS,12)==SUCCESS);
    ASSERT(addTrainingGroup(DS,13)==SUCCESS);
    ASSERT(addTrainingGroup(DS,14)==SUCCESS);
    ASSERT(addGladiator(DS,140,1400,14)==SUCCESS);
    ASSERT(addGladiator(DS,141,1400,11)==SUCCESS);
    ASSERT(addGladiator(DS,142,1400,12)==SUCCESS);
    ASSERT(addGladiator(DS,143,1400,13)==SUCCESS);
    ASSERT(addGladiator(DS,144,100,8)==SUCCESS);

    ASSERT(trainingGroupFight(DS,0,14,1,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==8);

    ASSERT(trainingGroupFight(DS,11,14,1,1)==SUCCESS);
    ASSERT(trainingGroupFight(DS,13,14,1,1)==FAILURE);//group 14 can't fight
    ASSERT(trainingGroupFight(DS,11,12,1,1)==SUCCESS);
    ASSERT(trainingGroupFight(DS,11,13,1,1)==SUCCESS);
    ASSERT(trainingGroupFight(DS,11,8,1,1)==SUCCESS);

    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==9);

    return true;
}

bool advancedTest3(void* DS){
    int min=0;
    for(int i=10000;i>=5;i--){
        ASSERT(addTrainingGroup(DS,i)==SUCCESS);
    }
    ASSERT(addTrainingGroup(DS,0)==SUCCESS);
    ASSERT(addTrainingGroup(DS,1)==SUCCESS);
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==0);

    for(int i=10000;i>=0;i--){
        ASSERT(addTrainingGroup(DS,i)==FAILURE);
    }

    for(int i=0;i<=10000;i++) {
        ASSERT(addGladiator(DS, 10 + i, 300 + i, i) == SUCCESS);
    }


    for(int i=0;i<=9998;i++){
        ASSERT(trainingGroupFight(DS,i,i+2,1,1)==SUCCESS);
        ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
        ASSERT(min==i+1);
    }


    return true;
}


bool RunTest(){
    InitTest();
    int* arr=new int[3];
    arr[0]=2;
    arr[1]=3;
    arr[2]=4;
    void* DS=init(3,arr);
    ASSERT(DS!=NULL);

    addTrainingGroupTest(DS);
    addGladiatorTest(DS);
    trainingGroupFightTest(DS);
    getMinGroupTest(DS);
    advancedTest1(DS);
    advancedTest2(DS);
    quit(&DS);

    void* DS2=init(3,arr);
    advancedTest3(DS2);
    quit(&DS2);

    delete[] arr;
    std::cout<<"SUCCESS"<<std::endl;
    return true;
}



int main(){
    RunTest();
    return 0;
}
