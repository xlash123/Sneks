#include "globals.h"

//Screen dimension constants
int global::screenWidth = 640;
int global::screenHeight = 480;
const bool global::canScreenSizeChange = true;
const int global::FPS = 60;

const int global::TARGET_FRAME_TIME = 1000 / global::FPS;

// SDL references
SDL_Window *global::window = NULL;

//The window renderer
SDL_Renderer *global::renderer = NULL;

TTF_Font *global::font = NULL;