#ifndef _SNEK_H

#define _SNEK_H

// The starting length of a snek when the game starts
#define SNEK_STARTING_LENGTH 3
// The starting and repeating allocated size for the snek body
#define SNEK_ALLOC_SIZE 100
// Amount of vertical between sneks at the start of the round
#define SNEK_START_SPACING 10
// Displacement from the side at the start of the round
#define SNEK_START_X_DIST (SNEK_STARTING_LENGTH + 2)

#include <SDL2/SDL.h>
#include <stdlib.h>

#include "../globals.h"
#include "Position.h"
#include "../controller/Controller.h"

// Enum for the snek direction
typedef enum {
    UP, RIGHT, DOWN, LEFT
} Direction;

// The state of a snek
typedef struct {
    // Positions of each body piece of the snek. Head is at [0]
    Position *body;
    // Length of the body
    size_t length;
    // The number of this player
    size_t playerNum;
    // If the snek is alive
    bool alive;
    // The controller of this player
    ControllerState controller;
    // The direction the snek is facing
    Direction direction;
    // The last game tick when this snek was polled. Used for netcode
    uint lastPolled;
} SnekState;

#include "../world/World.h"

// Possible colors of players
extern const SDL_Color PLAYER_COLORS[MAX_SNEKS];

namespace Snek {
    // Initialize snek
    void init(SnekState *snek);
    // Resets the snek to a given head y position and facing left or right
    void reset(SnekState *snek, int y, bool isRight);

    // Update the snek
    void update(SnekState *snek);
    // Grow the snek when it eats food
    void grow(SnekState *snek);
    /**
     * Render snek to the screen
     * @param snek - the state of the snek to draw
     * @param sideLength - the length of the side of one body piece
     */
    void draw(SnekState *snek, float scale);
    // Deallocate the snek
    void free(SnekState *snek);
};

#endif