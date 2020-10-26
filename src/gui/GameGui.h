#ifndef _GAMEGUI_H
#define _GAMEGUI_H

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