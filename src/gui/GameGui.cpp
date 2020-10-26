#include "GameGui.h"

GameGui::GameGui() : Gui({ 0, 0, global::screenWidth, global::screenHeight }) {
    
}

GameGui::~GameGui() {
    free(world);
    world = NULL;
}

void GameGui::onEvent(SDL_Event event) {
    if (world != NULL) {
        // TODO: Pass events on to controlls
    }
}

void GameGui::update() {
    if (world != NULL) {
        world->update();
    }
}

void GameGui::draw() {
    if (world != NULL) {
        world->draw();
    }
}