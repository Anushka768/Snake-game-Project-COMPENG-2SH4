
#include "Food.h"

Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos start(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'); //this is the first element in the list
    playerPosList->insertHead(start);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList; //delete the array list from the heap
}

const objPosArrayList* Player::getPlayerPos() const //copies the coordinates of the player's head to the objPos returnPos
{
    return playerPosList; //return the reference to the entire list
}

int Player::getSize() const
{
    return playerPosList->getSize();
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput(); //assigning to a variable makes it more readable within the code block

    if(input != 0)  // if not null character. Now, we are using the get input fn of the passed in GM class
    {
        switch(input)
        {                      
            case 27:  //escape char; exit
                mainGameMechsRef->setExitTrue(); //Pointer method of using fn to set exit flag to 1
                break;
            case 'w': //move 'up' or decrement y
                if (myDir != UP && myDir != DOWN) //AND; if either of these are true (UP for redundancy, and DOWN as the opposite direction), do not make the following change
                {
                    myDir = UP;
                }
                break;
            case 'a': //move 'left' or decrement x
                if (myDir != LEFT && myDir != RIGHT)
                {
                myDir = LEFT;
                }
                break;
            case 's': //move 'down' or increment y
                if (myDir != UP && myDir != DOWN)
                {
                myDir = DOWN;
                }
                break;
            case 'd': //move 'right' or increment x
                if (myDir != LEFT && myDir != RIGHT)
                {
                myDir = RIGHT;
                }
                break;
            default:
                break;
        }

        mainGameMechsRef->clearInput(); //once the input has been used, whether useful or not, it should be reset
    }          
}

void Player::movePlayer(bool grow)
{
    if (myDir == STOP)
        return;

    // get current head
    objPos head = playerPosList->getHeadElement();
    int newX = head.pos->x;
    int newY = head.pos->y;

    int maxX = mainGameMechsRef->getBoardSizeX();
    int maxY = mainGameMechsRef->getBoardSizeY();

    switch (myDir) // wrap-around movement
    {
        case UP:
            // newY--;
            if (--newY == 0)
                newY = maxY - 2;
            break;

        case DOWN:
            // newY++;
            if (++newY == maxY - 1)
                newY = 1;
            break;

        case LEFT:
            // newX--;
            if (--newX == 0)
                newX = maxX - 2;
            break;

        case RIGHT:
            // newX++;
            if (++newX == maxX - 1)
                newX = 1;
            break;

        default:
            break;
    }
    
    objPos bodyPart;
    for (int i = 0; i < playerPosList->getSize(); i++) //self collision check with all other snake segments
    {
        objPos bodyPart = playerPosList->getElement(i);  

        if (bodyPart.pos->x == newX && bodyPart.pos->y == newY) //self co
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            return;
        }
    }

    objPos newHead(newX, newY, '*'); 
    playerPosList->insertHead(newHead); // insert new head

    
    if (!grow) // only remove the tail if the snake did not eat/ate a super Food
    {
        playerPosList->removeTail();
    }
    

    if (playerPosList->getSize() >= (mainGameMechsRef->getValidSpaces() - 5)) //in the offchance a player is very good at snake, and the snake size is the entire usable board - 5 (for the 5 food items), the player has won
    {
        mainGameMechsRef->setWinFlag();
        mainGameMechsRef->setExitTrue(); //the player has won; exit the game
    }
}

objPos Player::getNextHeadPos() const //where this looks at the next position the head will be at
{
    objPos head = playerPosList->getHeadElement();
    int newX = head.pos->x;
    int newY = head.pos->y;

    int maxX = mainGameMechsRef->getBoardSizeX();
    int maxY = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
        case UP:
            if (--newY == 0)
                newY = maxY - 2;
            break;
        case DOWN:
            if (++newY == maxY - 1)
                newY = 1;
            break;
        case LEFT:
            if (--newX == 0)
                newX = maxX - 2;
            break;
        case RIGHT:
            if (++newX == maxX - 1)
                newX = 1;
            break;
        default:
            break;
    }

    objPos candidate(newX, newY, '*');
    return candidate;
}

   