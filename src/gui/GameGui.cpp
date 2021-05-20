#include "GameGui.h"

GameGui::GameGui() : Gui() {
	Game::init(&game);

	const int testNum = 8;
	SnekState sneks[testNum];

	// TODO: Add sneks with local controllers
	int i = 0;
	Snek::init(&sneks[i]);
	sneks[i].controller.type = KEYBOARD;
	Game::addSnek(&game, sneks[i]);

	for (i = 1; i < /* global::numControllers */ testNum; i++) {
		Snek::init(&sneks[i]);
		sneks[i].controller.type = GAMEPAD;
		Game::addSnek(&game, sneks[i]);
	}

	Game::reset(&game);
}

GameGui::~GameGui() {
	for (size_t i = 0; i < game.numSneks; i++) {
		Snek::free(&game.sneks[i]);
	}
}

void GameGui::onEvent(SDL_Event *event) {
    // Send updates to each snek's controller
	// Each controller is responsible for filtering which events apply to them
	for (size_t i = 0; i < game.numSneks; i++) {
		// Events only need to be sent to local sneks
		if (game.sneks[i].controller.type != REMOTE) {
			Controller::updateActions(&game.sneks[i].controller, event);
		}
	}
	if (event->type == SDL_KEYDOWN && event->key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		Game::reset(&game);
	}
}

void GameGui::update() {
    Game::update(&game);
}

void GameGui::draw() {
    // How large one pixel is
	float scale;
	// Location on the screen for where the game is rendered
	SDL_Rect worldViewport;
	if (global::screenWidth > global::screenHeight) {
		scale = (float) global::screenHeight / WORLD_HEIGHT;
		worldViewport = { (int) (global::screenWidth / 2 - (WORLD_WIDTH * scale) / 2), 0, (int) (WORLD_WIDTH * scale), (int) (WORLD_HEIGHT * scale) };
	} else {
		scale = global::screenWidth / WORLD_WIDTH;
		worldViewport = { 0, (int) ((global::screenHeight / 2) - ((WORLD_HEIGHT / 2) * scale)), (int) (WORLD_WIDTH * scale), (int) (WORLD_HEIGHT * scale) };
	}

	// Set the viewport and the scaling for the game
	SDL_RenderSetViewport(global::renderer, &worldViewport);

	// Set game background color
	{
		SDL_Color c = GAME_BACKGROUND_COLOR;
		SDL_SetRenderDrawColor(global::renderer, c.r, c.b, c.g, c.a);
		// Draw background color
		SDL_RenderFillRect(global::renderer, NULL);
	}

    // Draw the game
    Game::draw(&game, scale);

    // Undo the viewport
    SDL_RenderSetViewport(global::renderer, NULL);

    // Draw the boarder around the game
	SDL_SetRenderDrawColor(global::renderer, 0, 0xFF, 0, 0xFF);
	SDL_RenderDrawRect(global::renderer, &worldViewport);

	// Set scaling back to normal
	SDL_RenderSetScale(global::renderer, 1, 1);

    // TODO: Draw HUD displays
}