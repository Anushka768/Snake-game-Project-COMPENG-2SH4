#include <stdio.h>
#include "MacUILib.h"

// PPA2 GOAL: 
//       Construct the game backbone where the player can control an object 
//       to move freely in the game board area with border wraparound behaviour.

// Watch Briefing Video and Read Lab Manual before starting on the activity!



// PREPROCESSOR CONSTANTS DEFINITION HERE
/////////////////////////////////////////



// GLOBAL VARIABLE DEFINITION HERE
# define B_ROWS 10
# define B_COLS 20
# define BORDER '#'
# define PLAYER '@'

# define SPEED_1 300000 // slowest speed 
# define SPEED_2 200000
# define SPEED_3 100000 // default speed 
# define SPEED_4 60000
# define SPEED_5 30000 // fastest speed

/////////////////////////////////////////
int speed; // for modifying speed
int speed_level[5] = {SPEED_1, SPEED_2, SPEED_3, SPEED_4, SPEED_5 }; // array to stre and loop through the speed
int speed_index; //to set speed and display on screen the current speed level
int exitFlag; // Program Exiting Flag - old stuff

// For storing the user input - from PPA1
char input;

// [TODO] : Define objPos structure here as described in the lab document
struct objPos
{
    int x;
    int y;
    char symbol;
};

struct objPos player;

// [TODO] : Define the Direction enumeration here as described in the lab document
//          This will be the key ingredient to construct a simple Finite State Machine
//          For our console game backbone.

enum Direction { STOP, UP, DOWN, LEFT, RIGHT};
enum Direction playerDir;

// FUNCTION PROTOTYPING DEFINITION HERE
/////////////////////////////////////////

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// You may insert additional helper function prototypes below.
// 
// As a good practice, always insert prototype before main() and implementation after main()
// For ease of code management.



// MAIN PROGRAM LOOP
/////////////////////////////////////////
// This part should be intuitive by now.
// DO NOT TOUCH

int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();

}


// INITIALIZATION ROUTINE
/////////////////////////////////////////
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    input = 0; // NULL
    exitFlag = 0;  // not exiting    
    speed_index = 2 ; //default speed
    speed = speed_level[speed_index]; // the current speed being used 
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!
    player.x = B_COLS /2; // to position in centre of the border
    player.y = B_ROWS /2; // to position @ in centre of the border 
    player.symbol = PLAYER; // @ defined in beginning
    playerDir = STOP; // initial direction


}


// INPUT PROCESSING ROUTINE
/////////////////////////////////////////
void GetInput(void)
{
    // [TODO] : Implement Asynchronous Input - non blocking character read-in    
    //          (Same as PPA1)
    if (  MacUILib_hasChar()) {
        input = MacUILib_getChar(); // get user input
    }
    


}


// PROGRAM LOGIC ROUTINE
/////////////////////////////////////////
void RunLogic(void)
{
    // [TODO] : First, process the input by mapping
    //          WASD to the corresponding change in player object movement direction
    // W - up, S - Down, A - Left, D - Right
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                exitFlag = 1;
                break;

            // Add more key processing here
            case 'W': case 'w'://move up
                if (playerDir == LEFT || playerDir == RIGHT || playerDir == STOP)        
                    {playerDir = UP;}
                break;

            // Add more key processing here
            case 'S': case 's'://move down
                if (playerDir == LEFT || playerDir == RIGHT || playerDir == STOP)        
                    {playerDir = DOWN;}
                break;

            // Add more key processing here    
            case 'A': case 'a'://move left
                if (playerDir == UP || playerDir == DOWN || playerDir == STOP)        
                    {playerDir = LEFT;}
                break;
            
            // Add more key processing here    
             case 'D': case 'd'://move right
                if (playerDir == UP || playerDir == DOWN || playerDir == STOP)        
                    {playerDir = RIGHT;}
                break;

            // processing for speed 
            case '+':
                if (speed_index < 4) // to increase speed
                    {
                        speed_index++;
                        speed = speed_level[speed_index];
                    }
                break;

            case '-':
                if (speed_index > 0) // to decrease speed
                    {
                        speed_index--;
                        speed = speed_level[speed_index];
                    }
                break;

            default: // to exit the switch
                break;
        }
        input = 0;
    }



    // [TODO] : Next, you need to update the player location by 1 unit 
    //          in the direction stored in the program
    switch (playerDir)
    {
        case UP:
            player.y--;
            break;
        case DOWN:
            player.y++;
            break;
        case RIGHT:
            player.x++;
            break;
        case LEFT:
            player.x--;
            break;
        default: // to exit the switch
            break;
    }
    // [TODO] : Heed the border wraparound!!!

    if ( player.x >= B_COLS  - 1){
        player.x = 1;
    }
    else if ( player.x <= 0){
        player.x = B_COLS - 2;
    }

     if ( player.y >= B_ROWS  - 1){
        player.y = 1;
    }
    else if ( player.y <= 0){
        player.y = B_ROWS - 2;
    }
    
}



// SCREEN DRAWING ROUTINE
/////////////////////////////////////////
void DrawScreen(void)
{
    // [TODO] : Implement the latest drawing logic as described in the lab manual
    //
    //  1. clear the current screen contents
    MacUILib_clearScreen();
    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.

    //  3. For every visited character location on the game board
    //          If on border on the game board, print a special character
    //          If at the player object position, print the player symbol
    //          Otherwise, print the space character
    //     Think about how you can format the screen contents to achieve the
    //     same layout as presented in the lab manual

    //  4. Print any debugging messages as seen needed below the game board.
    //     As discussed in class, leave these debugging messages in the program
    //     throughout your dev process, and only remove them when you are ready to release
    //     your code. 
    int row , col;
     MacUILib_printf("\n Controls:  W/A/S/D = MOVE    SPACE = EXIT    +/- = CHANGE SPEED\n"); // diaplay buttons that can be used to control @
   for (row = 0; row < B_ROWS; row ++){
    for (col = 0; col < B_COLS; col++){
        if ( row == 0 || row == B_ROWS - 1 || col == 0 || col == B_COLS -1){ // print the border
            MacUILib_printf("%c", BORDER);
        }
        else if ( row == player.y && col == player.x){ // prints @
            MacUILib_printf("%c", player.symbol);
        }
        else  {MacUILib_printf(" ");}
    }
    MacUILib_printf("\n");
   }
   double delay = speed/100000.0; // calculating speed to display 
   MacUILib_printf("\n Current Speed: %d => %.2f s", speed_index + 1, delay); // display current speed

}




// PROGRAM LOOOP DELAYER ROUTINE
/////////////////////////////////////////
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    MacUILib_Delay(speed);    
}



// PROGRAM CLEANUP ROUTINE
/////////////////////////////////////////
// Recall from PPA1 - this is run only once at the end of the program
// for garbage collection and exit messages.
void CleanUp(void)
{
    MacUILib_uninit();
}



