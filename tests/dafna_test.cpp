#include <iostream>
#include "../Colosseum.h"

void test(){
    int exeption=0;
    int arr[]={2,1};
    Colosseum DS(2,arr); //Initial with Team:1,2
    int minGroup;

    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==1);
    DS.addTrainingGroup(0); //Add Team 0
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==0);

    DS.addGladiator(100,20,0); //Add Gladiator ID:100 Score:20 to Team:0
    DS.addGladiator(101,20,0); //Add Gladiator ID:101 Score:20 to Team:0
    DS.addGladiator(102,20,0); //Add Gladiator ID:102 Score:20 to Team:0

    DS.addGladiator(110,20,1); //Add Gladiator ID:110 Score:20 to Team:1
    DS.addGladiator(111,20,1);//Add Gladiator ID:111 Score:20 to Team:1

    DS.addGladiator(120,20,2); //Add Gladiator ID:120 Score:20 to Team:2
    DS.addGladiator(121,20,2); //Add Gladiator ID:121 Score:20 to Team:2
    DS.addGladiator(122,20,2); //Add Gladiator ID:122 Score:20 to Team:2

    DS.trainingGroupFight(0,2,3,3); //Team 2 lost
    try{
        DS.trainingGroupFight(0,2,3,3); //Team 2 is not Active
    }catch (ColosseumExceptions::Failure){
        exeption++; //exception=1
    }
    assert(exeption==1);
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==0);

    DS.trainingGroupFight(0,1,3,2); //Team 1 lost
    try {
        DS.trainingGroupFight(0,1,1,1); //Team 1 is not Active
    }
    catch (ColosseumExceptions::Failure) {
        exeption++; //exception=2
    }
    assert(exeption==2);

    DS.addTrainingGroup(3); //Add Team 3
    DS.addGladiator(130,30,3); //Add Gladiator ID:130 Score:30 to Team:3
    DS.addGladiator(131,30,3); //Add Gladiator ID:131 Score:30 to Team:3

    DS.trainingGroupFight(0,3,1,1); //Team 0 lost
    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==3);
    try {
        DS.trainingGroupFight(0,3,1,1); //Team 0 is not Active
    }
    catch (ColosseumExceptions::Failure) {
        exeption++; //exception=3
    }

    DS.addTrainingGroup(4); //Add Team 4
    DS.addGladiator(140,40,4); //Add Gladiator ID:140 Score:40 to Team:4
    DS.addGladiator(141,40,4); //Add Gladiator ID:141 Score:40 to Team:4
    DS.addGladiator(142,40,4); //Add Gladiator ID:142 Score:40 to Team:4

    DS.addTrainingGroup(5); //Add Team 5
    DS.addGladiator(150,50,5); //Add Gladiator ID:150 Score:50 to Team:5
    DS.addGladiator(151,50,5); //Add Gladiator ID:151 Score:50 to Team:5

    DS.trainingGroupFight(4,5,2,1); //Team 5 lost

    try {
        DS.trainingGroupFight(5,3,1,1); //Team 5 is not Active
    }
    catch (ColosseumExceptions::Failure) {
        exeption++; //exception=4
    }

    DS.addGladiator(135,300,3); //Add Gladiator ID:135 Score:300 to Team:3
    DS.trainingGroupFight(3,4,1,1); //Team 4 lost

    DS.getMinTrainingGroup(&minGroup);
    assert(minGroup==3);
    try {
        DS.trainingGroupFight(4,3,1,1); //Team 4 is not Active
    }
    catch (ColosseumExceptions::Failure) {
        exeption++; //exception=5
    }



    assert(exeption==5);

    std::cout << "Passed";
}

int main() {
    test();

    return 0;
}