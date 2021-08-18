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
#include "../controller/Controller.h"

/**
 * The strictly gameplay-related game information. This information will get synced with all
 * clients connected in this session.
 * */
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

/**
 * Metadata related to this game. This data will never be synced with remote players and is only
 * relevant to the local client.
 * */
typedef struct {
    // The index that the player uses for a controller. -1 for remote players
    int controllers[MAX_SNEKS];
} GameMeta;

namespace Game {
    // Initialize game state to default. Do not use to restart a game!
    void init(GameState *game);

    // Add a snek to the game. Return false if full
    bool addSnek(GameState *game, SnekState snek);

    // Reset the game and everything in it to a starting state
    void reset(GameState *game);

    // Reset a food's position to a non-snek location
    void resetFood(GameState *game, int foodIdx);

    // Receive input data and update the actions of each player. This will modify the game state
    void processInput(GameState *game, GameMeta *meta);

    // Progress to the next game frame
    GameState nextFrame(GameState *game);

    // Draw the world and everything in it
    void draw(GameState *game, float scale);

    // Roll another RNG number based on the RNG value in the game state
    long int nextRng(GameState *game);

    // Save the given game state into a byte stream
    void serialize(GameState *game, void **buffer);

    // Convert a byte steam into a ready-to-use game state
    void deserialize(void **buffer, GameState *game);
};

#endif