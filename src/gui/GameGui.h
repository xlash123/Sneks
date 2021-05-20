#ifndef _GAMEGUI_H
#define _GAMEGUI_H

#include <SDL2/SDL.h>

#define GAME_BACKGROUND_COLOR ((SDL_Color) { 0x37, 0x37, 0x37, 0xFF })

#include "../globals.h"
#include "Gui.h"
#include "../game/Game.h"

// A gui that wraps around the game world
class GameGui : public Gui {
public:
    // The current state of the game
    GameState game;

    GameGui();
    ~GameGui();

    // Take events and apply them to the controlls
    void onEvent(SDL_Event *event);

    // Update the game
    void update();
    
    // Renders the game
    void draw();
};

#endif