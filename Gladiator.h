//
// Created by user on 27/12/2017.
//

#ifndef WET2_GLADIATOR_H
#define WET2_GLADIATOR_H

class Gladiator{
private:
    int gladiatorId;
    int score;

public:
    //Constructor of the Gladiator with 0 parameters
    Gladiator() : gladiatorId(0), score(0){}

    //Constructor of the Gladiator
    //Parameters: the ID of the Gladiator
    //            the ID of the Trainer of the Gladiator
    //            the Levevl of the Gladiator
    Gladiator(int gladiatorId, int score) : gladiatorId(gladiatorId), score(score) {}

    //Copy Constructor of the Gladiator
    Gladiator(const Gladiator& gladiator) {
        this->gladiatorId=gladiator.gladiatorId;
        this->score=gladiator.score;
    }

    //Return the score of the Gladiator
    int getScore(){
        return this->score;
    }

    //Return the ID of the Gladiator
    int getID(){
        return this->gladiatorId;
    }

    //Operator < that decide which gladiator is smaller according to this:
    //If the Level of The First Gladiator is smaller than the Second, Then the
    // First Gladiator is smaller. If the Levels are equal than we check the ID,
    // and if the First one has bigger ID than he is smaller
    bool operator<(const Gladiator& glad) const {
        if(this->score < glad.score) {
            return true;
        }
        else if(this->score > glad.score) {
            return false;
        }
        else {
            if (this->gladiatorId > glad.gladiatorId) {
                return true;
            } else {
                return false;
            }
        }
    }

    //Operator > that decide which gladiator is bigger according to this:
    //If the Level of The First Gladiator is bigger than the Second, Then the
    // First Gladiator is bigger. If the Levels are equal than we check the ID,
    // and if the First one has smaller ID than he is bigger
    bool operator>(const Gladiator& glad) const {
        if(this->score > glad.score) {
            return true;
        }
        else if(this->score < glad.score) {
            return false;
        }
        else {
            if(this->gladiatorId < glad.gladiatorId) {
                return true;
            }
            else {
                return false;
            }
        }
    }

    //Operator == that decide if two Gladiators are equal according to this:
    //Two Gladiators are equal if the Level and the ID is the same
    bool operator==(const Gladiator& glad) const {
        if(this->score == glad.score && this->gladiatorId == glad.gladiatorId) {
            return true;
        }
        return false;
    }



};

#endif //WET2_GLADIATOR_H
