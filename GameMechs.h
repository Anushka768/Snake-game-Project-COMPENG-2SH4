#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

class Food;
#include "objPos.h"
#include "objPosArrayList.h"


using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        bool winFlag;
        int score;

        int boardSizeX;
        int boardSizeY;
        int validSpaces;

        objPos food;

        Food* currentFood = nullptr;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();
        int getWinFlagStatus() const;
        void setWinFlag();

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        int getValidSpaces() const;
        
        int getScore() const;
        void incrementScore(int amt); 
        
        // More methods should be added here
};

#endif