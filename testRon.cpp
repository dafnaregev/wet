#include <iostream>
#include "Colosseum.h"
#include <iostream>
#include "stdio.h"
#include "library2.h"


#define ASSERT(b) do { \
        if (!(b)) { \
                printf("\nAssertion failed at %s:%d %s\n",__FILE__,__LINE__,#b); \
                return false; \
        } \
} while (0)

//General Test with basic Structure
bool test1(){
    int arr[] = {300,320,330,310,350,290,280};
    void* DS = init(7, arr);
    assert(DS!=NULL);
    int min=0;
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);

    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==280);

    for (int i = 200 ; i >= 10 ; i -= 10) { //20 teams addad
        ASSERT(addTrainingGroup(DS,i)==SUCCESS);
        ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
        ASSERT(min==i);
    }

    for (int i = 200 ; i >= 10 ; i -= 10) { //ID already exists
        ASSERT(addTrainingGroup(DS,i)==FAILURE);
    }

    for (int j = 10; j <= 200 ; j+=10) {
        for (int i = j; i < j+10 ; ++i) {
            ASSERT(addGladiator(DS,i,i,j)==SUCCESS); //add glad with scores 10-19,20-29,30-39...
        }
    }

    for (int j = 10; j <= 200 ; j+=10) {
        for (int i = j; i < j+10 ; ++i) {
            ASSERT(addGladiator(DS,i,i,j)==FAILURE); //ID already exists
        }
    }

    for (int i = 601 ; i >= 401 ; i -= 20) { //11 teams addad
        ASSERT(addTrainingGroup(DS,i)==SUCCESS);
    }

    for (int i = 601 ; i >= 401 ; i -= 20) { //Id already exists
        ASSERT(addTrainingGroup(DS,i)==FAILURE);
    }

    for (int j = 401; j <= 601 ; j+=20) {
        for (int i = j; i < j+20 ; ++i) {
            ASSERT(addGladiator(DS,i,i,j)==SUCCESS);
        }
    }

    for (int j = 401; j <= 601 ; j+=20) {
        for (int i = j; i < j+20 ; ++i) {
            ASSERT(addGladiator(DS,i,i,j)==FAILURE); //Id already exists
        }
    }

    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==10);


    ASSERT(trainingGroupFight(DS,10,20,10,10)==SUCCESS);        //10 is gone
    ASSERT(trainingGroupFight(DS,80,10,1,1)==FAILURE);          //10 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==20);
    ASSERT(trainingGroupFight(DS,20,30,2,1)==SUCCESS);          //30 is gone
    ASSERT(trainingGroupFight(DS,80,30,1,1)==FAILURE);          //30 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==20);
    ASSERT(trainingGroupFight(DS,40,20,1,1)==SUCCESS);          //20 is gone
    ASSERT(trainingGroupFight(DS,80,20,1,1)==FAILURE);          //20 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==40);


    ASSERT(trainingGroupFight(DS,401,40,1,1)==SUCCESS);         //40 is gone
    ASSERT(trainingGroupFight(DS,80,40,1,1)==FAILURE);          //40 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==50);



    /*fight: 50(50,51,...,59) vs 60(60,61,...,69)*/
    ASSERT(addGladiator(DS,700,69,50)==SUCCESS);
    /*both have 69 score best glad, 50 with minimal id*/
    ASSERT(trainingGroupFight(DS,50,60,1,1)==SUCCESS);         //60 is gone
    ASSERT(trainingGroupFight(DS,80,60,1,1)==FAILURE);         //60 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==50);

    ASSERT(addGladiator(DS,701,79,50)==SUCCESS);
    ASSERT(addGladiator(DS,710,78,50)==SUCCESS);
    ASSERT(addGladiator(DS,703,70,50)==SUCCESS);
    ASSERT(addGladiator(DS,705,71,50)==SUCCESS);
    ASSERT(addGladiator(DS,706,76,50)==SUCCESS);
    ASSERT(addGladiator(DS,704,77,50)==SUCCESS);
    ASSERT(addGladiator(DS,708,72,50)==SUCCESS);
    ASSERT(addGladiator(DS,702,74,50)==SUCCESS);
    ASSERT(addGladiator(DS,707,73,50)==SUCCESS);
    ASSERT(addGladiator(DS,709,75,50)==SUCCESS);

    /*ID already exists*/
    ASSERT(addGladiator(DS,701,79,80)==FAILURE);
    ASSERT(addGladiator(DS,710,78,80)==FAILURE);
    ASSERT(addGladiator(DS,703,70,80)==FAILURE);
    ASSERT(addGladiator(DS,705,71,80)==FAILURE);
    ASSERT(addGladiator(DS,706,76,80)==FAILURE);
    ASSERT(addGladiator(DS,704,77,80)==FAILURE);
    ASSERT(addGladiator(DS,708,72,80)==FAILURE);
    ASSERT(addGladiator(DS,702,74,80)==FAILURE);
    ASSERT(addGladiator(DS,707,73,80)==FAILURE);
    ASSERT(addGladiator(DS,709,75,80)==FAILURE);

    ASSERT(trainingGroupFight(DS,50,70,5,4)==SUCCESS);         //70 is gone
    ASSERT(trainingGroupFight(DS,80,70,1,1)==FAILURE);         //70 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==50);

    ASSERT(trainingGroupFight(DS,50,90,2,1)==SUCCESS);         //90 is gone
    ASSERT(trainingGroupFight(DS,80,90,1,1)==FAILURE);         //90 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==50);

    ASSERT(trainingGroupFight(DS,50,100,1,1)==SUCCESS);        //50 is gone
    ASSERT(trainingGroupFight(DS,80,50,1,1)==FAILURE);         //50 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==80);



    for (int i = 100 ; i >= 50 ; i -= 10) {
        ASSERT(addTrainingGroup(DS,i)==FAILURE);
    }

    ASSERT(trainingGroupFight(DS,100,80,7,10)==SUCCESS);        //100 is gone
    ASSERT(trainingGroupFight(DS,80,100,1,1)==FAILURE);         //100 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==80);

    ASSERT(trainingGroupFight(DS,110,80,7,10)==SUCCESS);        //110 is gone
    ASSERT(trainingGroupFight(DS,80,110,1,1)==FAILURE);         //110 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==80);

    ASSERT(trainingGroupFight(DS,120,80,7,10)==SUCCESS);        //80 is gone
    ASSERT(trainingGroupFight(DS,80,120,1,1)==FAILURE);         //80 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==120);


    ASSERT(trainingGroupFight(DS,120,130,5,5)==SUCCESS);        //120 is gone
    ASSERT(trainingGroupFight(DS,130,120,1,1)==FAILURE);        //120 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==130);

    ASSERT(addGladiator(DS,711,150,130)==SUCCESS);
    ASSERT(addGladiator(DS,712,149,130)==SUCCESS);
    ASSERT(addGladiator(DS,713,148,130)==SUCCESS);

    ASSERT(trainingGroupFight(DS,140,130,3,3)==SUCCESS);        //140 is gone
    ASSERT(trainingGroupFight(DS,130,140,1,1)==FAILURE);        //140 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==130);

    ASSERT(trainingGroupFight(DS,150,130,3,4)==SUCCESS);        //150 is gone
    ASSERT(trainingGroupFight(DS,130,150,1,1)==FAILURE);        //150 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==130);

    ASSERT(addGladiator(DS,714,169,130)==SUCCESS);

    ASSERT(trainingGroupFight(DS,160,130,1,1)==SUCCESS);        //160 is gone
    ASSERT(trainingGroupFight(DS,130,160,1,1)==FAILURE);        //160 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==130);

    ASSERT(trainingGroupFight(DS,170,130,10,1)==SUCCESS);       //130 is gone
    ASSERT(trainingGroupFight(DS,130,180,1,1)==FAILURE);        //130 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==170);

    ASSERT(addGladiator(DS,715,189,170)==SUCCESS);
    ASSERT(addGladiator(DS,717,184,170)==SUCCESS);
    ASSERT(addGladiator(DS,718,188,170)==SUCCESS);
    ASSERT(addGladiator(DS,716,187,170)==SUCCESS);
    ASSERT(addGladiator(DS,719,185,170)==SUCCESS);

    ASSERT(trainingGroupFight(DS,170,180,6,6)==SUCCESS);        //170 is gone
    ASSERT(trainingGroupFight(DS,170,200,1,1)==FAILURE);        //170 is not active
    ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
    ASSERT(min==180);

    quit(&DS);
    std::cout << "Passed_1 " << std::endl;
    return true;

}


bool test2() {
    int arr[2] = {100000,200000};
    void* DS = init(2, arr);
    assert(DS!=NULL);
    int min=0;
    ASSERT(getMinTrainingGroup(DS,&min)==SUCCESS);
    ASSERT(min==100000);
    int counter=2;
    for (int i = 99999 ; i >= 0 ; i--) {
        ASSERT(addTrainingGroup(DS,i)==SUCCESS);
        ASSERT(getMinTrainingGroup(DS, &min)==SUCCESS);
        ASSERT(min==i);
        ++counter;

    }

    for (int j = 0; j <= 100000 ; j++) {
        ASSERT(addGladiator(DS,j,j,j)==SUCCESS);
    }

    for (int j = 0; j <= 100000 ; j++) {
        ASSERT(addGladiator(DS,j+100001,j,j)==SUCCESS);
    }
    quit(&DS);
    std::cout << "Passed_2 " << std::endl;
    return true;
}

int main() {
    test1();
    test2();
    return 0;
}
