#include "globals.h"

//Screen dimension constants
int global::screenWidth = 640;
int global::screenHeight = 480;
const bool global::canScreenSizeChange = true;
const size_t global::FPS = 60;

const uint32_t global::TARGET_FRAME_TIME = (uint32_t) (1000 / global::FPS);

// SDL references
SDL_Window *global::window = NULL;

//The window renderer
SDL_Renderer *global::renderer = NULL;

TTF_Font *global::font = NULL;