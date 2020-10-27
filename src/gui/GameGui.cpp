#include "GameGui.h"

GameGui::GameGui() : Gui() {
	World::init(&world);

	const int testNum = 8;
	SnekState sneks[testNum];

	for (int i = 0; i < testNum; i++) {
		Snek::init(&sneks[i]);
		sneks[i].controller.type = KEYBOARD;
		World::addSnek(&world, sneks[i]);
	}

	World::reset(&world);
}

GameGui::~GameGui() {
	for (size_t i = 0; i < world.numSneks; i++) {
		Snek::free(&world.sneks[i]);
	}
}

void GameGui::onEvent(SDL_Event *event) {
    // Send updates to each snek's controller
	// Each controller is responsible for filtering which events apply to them
	for (size_t i = 0; i < world.numSneks; i++) {
		// Events only need to be sent to local sneks
		if (world.sneks[i].controller.type != REMOTE) {
			Controller::updateActions(&world.sneks[i].controller, event);
		}
	}
}

void GameGui::update() {
    World::update(&world);
}

void GameGui::draw() {
    // How large one pixel is
	float scale;
	// Location on the screen for where the world is rendered
	SDL_Rect worldViewport;
	if (global::screenWidth > global::screenHeight) {
		scale = (float) global::screenHeight / WORLD_HEIGHT;
		worldViewport = { (int) (global::screenWidth / 2 - (WORLD_WIDTH * scale) / 2), 0, (int) (WORLD_WIDTH * scale), (int) (WORLD_HEIGHT * scale) };
	} else {
		scale = global::screenWidth / WORLD_WIDTH;
		worldViewport = { 0, (int) ((global::screenHeight / 2) - ((WORLD_HEIGHT / 2) * scale)), (int) (WORLD_WIDTH * scale), (int) (WORLD_HEIGHT * scale) };
	}

	// Set the viewport and the scaling for the world
	SDL_RenderSetViewport(global::renderer, &worldViewport);

    // Draw the world
    World::draw(&world, scale);

    // Undo the viewport
    SDL_RenderSetViewport(global::renderer, NULL);

    // Draw the boarder around the world
	SDL_SetRenderDrawColor(global::renderer, 0, 0xFF, 0, 0xFF);
	SDL_RenderDrawRect(global::renderer, &worldViewport);

	// Set scaling back to normal
	SDL_RenderSetScale(global::renderer, 1, 1);

    // TODO: Draw HUD displays
}