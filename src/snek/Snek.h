#ifndef _SNEK_H

#define _SNEK_H

#include <SDL2/SDL.h>
#include <stdlib.h>

#include "../globals.h"

// The starting length of a snek when the game starts
#define SNEK_STARTING_LENGTH 3

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
    // The controller of this player
    Controller *controller;
    // The direction the snek is facing
    Direction direction;
    // The last game tick when this snek was polled. Used for netcode
    uint lastPolled;
} SnekState;

#include "../controller/Controller.h"
#include "../world/World.h"
#include "Position.h"

// Possible colors of players
const SDL_Color PLAYER_COLORS[MAX_SNEKS];

namespace Snek {
    // Update the snek
    void update(SnekState *snek);
    // Grow the snek when it eats food
    void grow(SnekState *snek);
    /**
     * Render snek to the screen
     * @param snek - the state of the snek to draw
     * @param sideLength - the length of the side of one body piece
     */
    void draw(SnekState *snek);
};

#endif