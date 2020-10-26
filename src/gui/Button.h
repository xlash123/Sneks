#ifndef _BUTTON_H

#define _BUTTON_H

#include "Widget.h"

class Button : Widget {
public:
	void onEvent(SDL_Event event);
};

#endif