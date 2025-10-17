# Game-Board-with-Free-Moving-Player-Object
The Game Board Player Project is a console-based interactive program built in C that simulates a 20×10 game board with a free-moving player object.
The player can move asynchronously using keyboard controls (W, A, S, D) and wraps around the board edges, creating a smooth, continuous motion effect.

# Features
- 20×10 dynamic game board with customizable ASCII borders and player icon.
- Real-time movement using W, A, S, D keys for directional control.
- Smooth wraparound motion when reaching screen edges.
- Adjustable speed settings for different gameplay levels.
- Instant response input without interrupting gameplay.
- Simple exit command (Space key) to safely end the program.

# Concepts & Skills Demonstrated
- Implemented Finite State Machine using enum for smooth directional control.
- Used structs to store player position and symbol efficiently.
- Applied asynchronous input handling with MacUILib for real-time movement.
- Built dynamic board rendering and wraparound logic using nested loops.
- Added adjustable speed control with array-based delay management.
- Debugged efficiently in VS Code using breakpoints and live variable tracking.

# How to Run
- Clone the repository:
git clone <repo-link>
cd <repo-folder>
- Open the folder in VS Code.
- Build the program using:
command: make
- Run the executable:
command: ./PPA2
- Controls:
W / A / S / D → Move
+ / - → Change speed
Space → Exit
