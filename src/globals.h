#ifndef _SNEK_GLOBALS_H

#define _SNEK_GLOBALS_H

#define MAX_CONTROLLERS 8

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdio.h>
#include <sstream>

#include "controller/Controller.h"

namespace global {
	// Current width of the screen
	extern int screenWidth;
	// Current height of the screen
	extern int screenHeight;
	// Whether this platform supports screen resizing
	extern const bool canScreenSizeChange;

	// The target framerate
	extern const size_t FPS;
	// The target time between frames
	extern const uint32_t TARGET_FRAME_TIME;

	// SDL references

	// The SDL window ref
	extern SDL_Window* window;
	// The SDL renderer
	extern SDL_Renderer *renderer;
	// The SDL font
	extern TTF_Font *font;
	// List of connected controllers (0 is always keyboard)
	extern ControllerState *controllers[MAX_CONTROLLERS];
	extern int numControllers;
}

#endif