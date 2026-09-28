# Snake Game

## Game Overview

This is a terminal-based Snake game written in C++. The player steers a snake around a 30-by-15 board, collects food to increase the score, and tries to grow as long as possible without running into the snake's own body.

## Requirements

- macOS with the Xcode Command Line Tools installed
- `g++`, `make`, and the `ncurses` library

## Build and Run

Open a terminal in this project folder and run:

```sh
make clean
make
./Project
```

The game runs in the terminal. Press `Esc` to quit. If the shutdown prompt appears, press Enter.

## Controls

- `W`: move up
- `A`: move left
- `S`: move down
- `D`: move right
- `Esc`: quit

The snake starts moving after the first direction key is pressed. It cannot immediately reverse into the opposite direction.

## Rules

- The board has five food items: four regular foods (`f`) and one super food (`F`).
- Eating regular food adds 1 point and grows the snake.
- Eating super food adds 10 points and does not grow the snake.
- Eaten food reappears at a new, unoccupied location.
- The snake wraps around the board when it reaches an edge.
- Running into the snake's own body ends the game.
- The game is won when the snake reaches the board's win-length threshold.

## Contributors

- Anushka Chauhan
- Andrew Honoris
