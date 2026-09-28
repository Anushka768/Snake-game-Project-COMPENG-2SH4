#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false; //all set to false initially
    winFlag = false;
    score = 0;

    boardSizeX = 30; //default size is 30 by 15
    boardSizeY = 15;
    validSpaces = ((boardSizeX - 2) * (boardSizeY - 2)); //this is essentially only to check the win condition (snake takes up all valid spaces, ie everything but the borders and the food spaces)
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;
    validSpaces = ((boardSizeX - 2) * (boardSizeY - 2));
}

// an explicit destructor is not needed. Nothing is made on the heap, so the implicit destructor will work fine

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

int GameMechs::getWinFlagStatus() const
{
    return winFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore(int amt)
{
    score += amt; //This now accounts for the above and beyond feature; we can now specify the score added within the subclasses
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

int GameMechs::getValidSpaces() const
{
    return validSpaces; 
}

void GameMechs::setExitTrue()
{
    exitFlag = true; //when the player stops playing in general. Further specificity such as the loseFlag is possible
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; //when the player specifically loses, ie crashes into themselves
}

void GameMechs::setWinFlag()
{
    winFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here