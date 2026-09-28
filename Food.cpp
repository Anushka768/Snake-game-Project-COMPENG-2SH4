#include "Food.h"

Food::Food(GameMechs *thisGMRef, Player *thisPlayerRef, const objPosArrayList *playerALRef, objPosArrayList *foodALRef, int index)
{   
    mainGameMechsRef = thisGMRef;
    playerArrayList = playerALRef; //pass in an objPos array list so it is known which coordinates are not valid/occupied
    foodArrayList = foodALRef;
}

Food::~Food() {} //an explicit destructor is not needed. Nothing is made on the heap

void Food::generateFood(const objPosArrayList* playerArrayList, objPosArrayList* foodArrayList) //both the body array list and the food bin array list are passed in separately as one is static sized, and one is dynamic
{
    while (true) //this loops repeats indefinitely until the coordinate pairs are all unique. Once they are, return out of the function
    {
        bool isUnique = true;

        foodPos.pos->x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1; //rerun the same routine until a new unique coordinate pair is found
        foodPos.pos->y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        // Check against the entire snake body
        for (int i = 0; i < playerArrayList->getSize(); i++)
        {
            const objPos &p = playerArrayList->getElement(i);

            if (foodPos.pos->x == p.pos->x && foodPos.pos->y == p.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        for (int i = 0; i < foodArrayList->getSize() && isUnique; i++) // Check against existing food
        {    
            const objPos &f = foodArrayList->getElement(i);

            if (foodPos.pos->x == f.pos->x && foodPos.pos->y == f.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            foodPos.symbol = 'f'; //normal food character
            foodArrayList->insertTail(foodPos);
            return;
        }
    }
}

void Food::regenerateFood(const objPosArrayList* playerArrayList, objPosArrayList* foodArrayList, int index)
{
    while (true)
    {
        bool isUnique = true;

        foodPos.pos->x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1; //rerun the same routine until a new unique coordinate pair is found
        foodPos.pos->y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        // Check against snake body
        for (int i = 0; i < playerArrayList->getSize(); i++)
        {
            const objPos &p = playerArrayList->getElement(i);

            if (foodPos.pos->x == p.pos->x && foodPos.pos->y == p.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        // Check against existing food
        for (int i = 0; i < foodArrayList->getSize() && isUnique; i++)
        {
             if (i == index) continue;
             
             const objPos &f = foodArrayList->getElement(i);

            if (foodPos.pos->x == f.pos->x && foodPos.pos->y == f.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            foodPos.symbol = 'f';
            foodArrayList->updateElement(index, foodPos);
            return;
        }
    }
}

void Food::addScore()
{
    mainGameMechsRef->incrementScore(1); 
}

objPos Food::getFoodPos() const
{
    objPos copy; //make a copy with the coordinates
    copy.pos->x = foodPos.pos->x;
    copy.pos->y = foodPos.pos->y;
    copy.symbol = foodPos.symbol; //this is necessary in order to print the food character

    return copy;
}


void supFood::generateFood(const objPosArrayList* playerArrayList, objPosArrayList* foodArrayList) //overriding the default one. To generate food in the start
{
   
    while (true)
    {
        bool isUnique = true;

        foodPos.pos->x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
        foodPos.pos->y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        for (int i = 0; i < playerArrayList->getSize(); i++)
        {
            const objPos &p = playerArrayList->getElement(i);

            if (foodPos.pos->x == p.pos->x && foodPos.pos->y == p.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        for (int i = 0; i < foodArrayList->getSize(); i++)
        {
            const objPos &f = foodArrayList->getElement(i);
            if (foodPos.pos->x == f.pos->x && foodPos.pos->y == f.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            foodPos.symbol = 'F'; //superFood character
            foodArrayList->insertTail(foodPos);
            return;
        }
    }
}

void supFood::regenerateFood(const objPosArrayList* playerArrayList, objPosArrayList* foodArrayList, int index) //overriding the default one. To update a singular fruit from the 5 
{
    while (true)
    {
        bool isUnique = true;

        foodPos.pos->x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
        foodPos.pos->y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        for (int i = 0; i < playerArrayList->getSize(); i++)
        {
            const objPos &p = playerArrayList->getElement(i);

            if (foodPos.pos->x == p.pos->x &&
                foodPos.pos->y == p.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        for (int i = 0; i < foodArrayList->getSize(); i++)
        {
            if (i == index) continue;

            const objPos &f = foodArrayList->getElement(i);
            if (foodPos.pos->x == f.pos->x &&
                foodPos.pos->y == f.pos->y)
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            foodPos.symbol = 'F';
            foodArrayList->updateElement(index, foodPos);
            return;
        }
    }
}

void supFood::addScore()
{
    mainGameMechsRef->incrementScore(10); //a special fruit will increment score by 10 points
}