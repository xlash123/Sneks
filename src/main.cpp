#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "globals.h"
#include "gui/Gui.h"

// Initialze SDL components and game state
bool init();

// The main game loop
void gameLoop();

int main(int argc, char const **argv)
{
    if (init) {
        // Start game loop
    } else {
        // SDL errors occured
        return 1;
    }
    return 0;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize: %s\n", SDL_GetError());
        return false;
    }

    global::window = SDL_CreateWindow("Sneks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global::screenWidth, global::screenHeight, SDL_WINDOW_SHOWN);

    if (global::window == NULL) {
        printf("Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    global::renderer = SDL_GetRenderer(global::window);

    return true;
}

void gameLoop() {

}