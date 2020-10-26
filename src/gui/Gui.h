#ifndef _SNEKS_GUI_H
#define _SNEKS_GUI_H

#include <SDL2/SDL.h>
#include <vector>

class Gui {
public:
    Gui();
    virtual ~Gui();

    // Do some acton with the given SDL Event
    virtual void onEvent(SDL_Event *event);
    // Update components due to game tick
    virtual void update();
    // Renders the gui to the screen
    virtual void draw() = 0;
};

/**
 * A 'stack' for the gui. Controlled as a stack, but accessed as an array to draw.
 * The stack allows for drawing all, but only updating the top gui.
 */
extern std::vector<Gui*> gui_stack;

#endif