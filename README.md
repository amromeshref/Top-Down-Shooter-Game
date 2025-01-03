# Top-Down Shooter Game

A simple top-down shooter game implemented using OpenGL and GLUT. Control a player character, shoot bullets to destroy incoming enemies, and earn points while avoiding collisions.

## Features
- **Player Controls**: Move using `W`, `A`, `S`, and `D` keys. Shoot bullets with the `Spacebar`.
- **Enemies**: Randomly spawned enemies descend from the top of the screen.
- **Collision Detection**: Bullets destroy enemies, and points are awarded for each enemy destroyed.
- **Score Display**: Real-time score display in the top-left corner of the screen.

## Controls
- `W`: Move up
- `A`: Move left
- `S`: Move down
- `D`: Move right
- `Spacebar`: Shoot bullets

## Installation
1. Clone this repository:
    ```bash
    git clone https://github.com/amromeshref/Top-Down-Shooter-Game.git
    cd Top-Down-Shooter-Game
    ```

2. Ensure you have the required dependencies installed:
    - **OpenGL**
    - **GLUT** (FreeGLUT or similar)

3. Compile the program:
    ```bash
    g++ -o game game.cpp -lGL -lGLU -lglut
    ```

4. Run the game:
    ```bash
    ./game
    ```
