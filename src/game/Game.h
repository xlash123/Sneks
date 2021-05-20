#ifndef _GAME_H
#define _GAME_H

// The max number of sneks allowed in a world. Not configurable
#define MAX_SNEKS 8
// The absolute max amount of food. Does not necessarily pertain to the world's current config
#define MAX_FOOD 64

#define WORLD_WIDTH 60
#define WORLD_HEIGHT 60

#include <stdlib.h>

#include "../globals.h"
#include "../snek/Snek.h"
#include "../snek/Food.h"

// The state of a world. Also serves as the game state
typedef struct {
    // Array of sneks
    SnekState sneks[MAX_SNEKS];
    // Array of foods
    FoodState food[MAX_FOOD];
    // Max size of food array. Configured for the world
    size_t maxFood;
    // Current number of elements in sneks array
    size_t numSneks;
    // The state of the rng
    unsigned int rng;
} GameState;

namespace Game {
    // Initialize game state to default. Do not use to restart a game!
    void init(GameState *game);

    // Add a snek to the game. Return false if full
    bool addSnek(GameState *game, SnekState snek);

    // Reset the game and everything in it to a starting state
    void reset(GameState *game);

    // Reset a food's position to a non-snek location
    void resetFood(GameState *game, int foodIdx);

    // Progress to the next game frame
    void update(GameState *game);

    // Draw the world and everything in it
    void draw(GameState *game, float scale);
};

#endif