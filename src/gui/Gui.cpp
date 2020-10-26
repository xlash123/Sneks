#include "Gui.h"

Gui::Gui(SDL_Rect viewport) {
    this->viewport = viewport;
}

// These gui functions are meant to be override, but aren't required to be

Gui::~Gui() {}

void Gui::onEvent(SDL_Event event) {}

void Gui::update() {}