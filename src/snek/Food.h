#ifndef _FOOD_H

#define _FOOD_H

#include <SDL2/SDL.h>

#include "../globals.h"
#include "Position.h"

#define FOOD_COLOR ((SDL_Color) { 0xFF, 0xFF, 0x00, 0xFF })

// Note: I could probably put the power ups in the food
// The state of a food
typedef struct {
	Position pos;
} FoodState;

// Food-based functions
namespace Food {
	// Draw the food to the screen
	void draw(FoodState *food);
};

#endif