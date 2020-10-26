#ifndef _WORLD_H
#define _WORLD_H

// The max number of sneks allowed in a world. Not configurable
#define MAX_SNEKS 8
// The absolute max amount of food. Does not necessarily pertain to the world's current config
#define MAX_FOOD 64

#define WORLD_WIDTH 60
#define WORLD_HEIGHT 60

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
    // Current number of elements in food array
    size_t numFood;
} WorldState;

namespace World {
    void init(WorldState *world);

    // Add a snek to the world. Return false if full
    bool addSnek(WorldState *world, SnekState snek);

    // Update the world and everything in it
    void update(WorldState *world);
    // Draw the world and everything in it
    void draw(WorldState *world, float scale);
};

#endif