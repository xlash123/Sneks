#ifndef _GAMEGUI_H
#define _GAMEGUI_H

#include <SDL2/SDL.h>

#define GAME_BACKGROUND_COLOR ((SDL_Color) { 0x37, 0x37, 0x37, 0xFF })

#include "../globals.h"
#include "Gui.h"
#include "../world/World.h"

// A gui that wraps around the game world
class GameGui : public Gui {
public:
    // The game world
    WorldState world;

    GameGui();
    ~GameGui();

    // Take events and apply them to the controlls
    void onEvent(SDL_Event *event);
    // Update the world
    void update();
    // Renders the world
    void draw();
};

#endif