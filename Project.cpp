#include <iostream>
#include <time.h>
#include <cstdlib>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 150000 //0.15 s
#define foodBinSize 5 //for above and beyond; define the bin size which contains all 5 foods

//bool exitFlag; //no longer needed as now we are using the exitFlag from GM

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player* playerPtr; //player object; includes the array list for all body segments
GameMechs* gmPtr;
Food** foodBin; //bin for the food objects
objPosArrayList* foodALPtr; //stores the coordinates for the food items

int main(void)
{

    Initialize();

    while(gmPtr->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    srand(time(NULL)); //seed the rng using the current time

    gmPtr = new GameMechs();
    foodALPtr = new objPosArrayList(foodBinSize); //this makes the sizing less wasteful

    
    foodBin = new Food*[foodBinSize]; //allocate 5 Food objects on the heap
    playerPtr = new Player(gmPtr);
    for (int i = 0; i < foodBinSize - 1; i++) //generate the food items
    {
        foodBin[i] = new Food(gmPtr, playerPtr, static_cast<const objPosArrayList*>(playerPtr->getPlayerPos()),foodALPtr, i); //getPlayerPos() must be set to const in order to be passed into the Food constructor
        foodBin[i]->generateFood(playerPtr->getPlayerPos(), foodALPtr);
    }
    foodBin[4] = new supFood(gmPtr, playerPtr, static_cast<const objPosArrayList*>(playerPtr->getPlayerPos()), foodALPtr, 4); //the last food item, the 5th, is a super food
    foodBin[4]->generateFood(playerPtr->getPlayerPos(), foodALPtr);

}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        gmPtr->setInput(MacUILib_getChar()); //set the input within game mechanics
    }
}

void RunLogic()
 {
    playerPtr->updatePlayerDir();
    objPos nextHead = playerPtr->getNextHeadPos(); //predict where the head will be after 1 move
    bool willEat = false; // check if there is a food at that location after 1 move
    int eatIndex = -1;

    for (int i = 0; i < foodALPtr->getSize(); ++i) // check all food items in the array to see which one matches the one we are going to collide with
    {
        objPos foodPos = foodALPtr->getElement(i);
        
        if (nextHead.pos->x == foodPos.pos->x && nextHead.pos->y == foodPos.pos->y) // if the food being collided with is found
        {
            willEat = true; //a bool which checks if the next position is a food. The snake is expected to eat (and thus grow)
            eatIndex = i; // store the index as this index will have its food replaced
            break;
        }
    }
    
    if (willEat && eatIndex >= 0) // for score and regeneration of food eaten
    {
        
        foodBin[eatIndex]->addScore();
        
        delete foodBin[eatIndex]; // delete the eaten food from array
        if (eatIndex == 4) // regenerate correct type food in same location in array
        {
            willEat = false; //willEat is set back to false if a super food is eaten, as the snake should not grow
            foodBin[eatIndex] = new supFood(gmPtr, playerPtr, static_cast<const objPosArrayList*>(playerPtr->getPlayerPos()), foodALPtr, eatIndex);
        }
        else
        {
            foodBin[eatIndex] = new Food(gmPtr, playerPtr,static_cast<const objPosArrayList*>(playerPtr->getPlayerPos()), foodALPtr, eatIndex);
        }
        
        foodBin[eatIndex]->regenerateFood(playerPtr->getPlayerPos(), foodALPtr, eatIndex); // regenerate food at the same location in the array list
        foodALPtr->updateElement(eatIndex, foodBin[eatIndex]->getFoodPos());
    }

    playerPtr->movePlayer(willEat); //grow the snake if willEat = true (ie normal food eaten). Otherwise (normal movement or superFood eaten), move normally
}


void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int i = 0; i < gmPtr->getBoardSizeY(); i++) //length 15; # of rows. y values
    {        
        for (int j = 0; j < gmPtr->getBoardSizeX(); j++) //width 30; # of chars per row. x values
        {
            if (i == 0 || i == gmPtr->getBoardSizeY() - 1) //top/bottom edges (0 or 14, in the default case); 15 #'s
            {
                MacUILib_printf("#");
                continue; //iterate next loop;
            }   
            else if (j == 0 || j == gmPtr->getBoardSizeX() - 1) //left/right edges (0 or 19 in the default case)
            {
                MacUILib_printf("#");
                continue;
            }
            else //the else case is quite different than before; it will capture a snake body segment or a food item or a blank ' ', as it is necessary to loop through every body/food coordinate to see if they match
            {
                int somethingPrinted = 0; //check if either a snake segment/food item has been printed. If not, print a ' '
                for (int k = 0; k < playerPtr->getPlayerPos()->getSize(); k++)
                {
                    if (i == playerPtr->getPlayerPos()->getElement(k).pos->y && j == playerPtr->getPlayerPos()->getElement(k).pos->x)
                    {
                        MacUILib_printf("%c", playerPtr->getPlayerPos()->getElement(k).symbol);
                        somethingPrinted = 1;
                        break;
                    }
                }
                for (int k = 0; k < foodALPtr->getSize(); k++)
                {
                    if (i == foodALPtr->getElement(k).pos->y && j == foodALPtr->getElement(k).pos->x) //spot is occupied by food item
                    {
                        MacUILib_printf("%c", foodBin[k]->getFoodPos().symbol);
                        somethingPrinted = 1;
                        break;
                    }
                }
                if (not somethingPrinted)
                {
                    MacUILib_printf(" "); //in the case that neither a snake segment nor a food item is printed, it is simply ' '
                }
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Welcome to Andrew's and Anushka's Snake Game! Press ESC to leave.\nHint: try eating the 'F' foods!\nScore: %d\n", gmPtr->getScore());
    
    if (gmPtr->getExitFlagStatus()) //if exitFlag is true, start preparing to exit the program
    {
        if (gmPtr->getLoseFlagStatus()) //further condition; if the player is leaving specifically because they lost, display this message instead
        {
            MacUILib_printf("You lost. Thank you for playing!\n"); //should this be in cleanup instead? ie cleaning up to put the final statement, which is this
        }
        else if (gmPtr->getWinFlagStatus()) //in the offchance that the snake takes up the entire board except the 5 food items (28 * 13 - 5), the player has won
        {
            MacUILib_printf("Wow, you actually won! Congratulations! Thank you for playing!");
        }
        else
        {
            MacUILib_printf("You are leaving without winning.\n");
        }
    }
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.15s delay.
}


void CleanUp(void)
{
    // MacUILib_clearScreen(); //this leads to clearing the screen after the game over message is shown,  making it only show up for a split second. Do not clear screen again
    
    delete playerPtr;
    delete gmPtr;
    delete foodALPtr;
    for (int i = 0 ; i < foodBinSize; i++)
    {
        delete foodBin[i]; //each fruit itself is on the heap. Delete it
    }
    delete[] foodBin; //delete the entire foodBin


    MacUILib_uninit();
    MacUILib_clearScreen(); //clear screen after properly exiting
}
