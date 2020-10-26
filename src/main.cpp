#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "globals.h"
#include "gui/Gui.h"
#include "gui/GameGui.h"

// Initialze SDL components and game state
bool init();

// The main game loop
void gameLoop();

int main()
{
    if (init()) {
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

    gui_stack.clear();
    gui_stack.push_back(new GameGui());

    return true;
}

void gameLoop() {
    // Set to false to kill the game
    bool alive = true;
    // SDL event
    SDL_Event event;

    // Start time for the entire frame
    uint32_t startTime = 0;
    // End time for game updating
    uint32_t endTimeUpdate = 0;
    // End time for rendering
    uint32_t endTimeRender = 0;

    while (alive) {
        startTime = SDL_GetTicks();

        // Update phase

        // Gui at the top of the gui stack
        Gui *currentGui = gui_stack.back();

        // Handle events
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    // Kill game when the X in the window is clicked
                    alive = false;
                    break;
                case SDL_WINDOWEVENT:
                    // Check if window was resized
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_GetRendererOutputSize(global::renderer, &global::screenWidth, &global::screenHeight);
                    }
                default:
                    ;
            }

            // Pass event to current gui
            currentGui->onEvent(&event);
        }

        // Update top gui
        currentGui->update();

        endTimeUpdate = SDL_GetTicks();

        // Render phase
        SDL_SetRenderDrawColor(global::renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(global::renderer);
        // Render guis
        size_t guiStackSize = gui_stack.size();
        for (size_t i = 0; i < guiStackSize; i++) {
            gui_stack[i]->draw();
        }
        // Render to the screen
        SDL_RenderPresent(global::renderer);

        endTimeRender = SDL_GetTicks();

        // Compute and limit FPS
        // Total amount of time spent in game logic
        uint32_t totalUpdateTime = startTime - endTimeUpdate;
        // Total amount of time spent rendering
        uint32_t totalRenderTime = endTimeUpdate - endTimeRender;
        // The total time spent in this frame
        uint32_t totalTime = totalUpdateTime + totalRenderTime;
        
        // Limit framerate
        if (totalTime < global::TARGET_FRAME_TIME) {
            SDL_Delay(global::TARGET_FRAME_TIME - totalTime);
        }
    }
}