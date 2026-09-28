#ifndef PLAYER_H
#define PLAYER_H

class Food;
class GameMechs;

#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        const objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer(bool grow); //this bool checks if the player has grown or not. Unique logic will occur depending on the bool
        objPos getNextHeadPos() const;
        // More methods to be added here
        void setFoodRefs(Food** foodBinRef, objPosArrayList* foodListRef); //sets up the reference to the relevant food objects: the food bin and food array list
        int getSize() const;
    private:
        objPosArrayList* playerPosList;
        enum Dir myDir;
        
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        objPosArrayList* foodALPtr = nullptr;
        Food** foodArray = nullptr; 
};

#endif