#include "World.h"

bool World::addSnek(WorldState *world, SnekState snek) {
	if (world->numSneks < MAX_SNEKS) {
		world->sneks[world->numSneks++] = snek;
		return true;
	}

	return false;
}

void World::update(WorldState *world) {
	// Update all sneks in the world
	for (size_t i = 0; i < world->numSneks; i++) {
		Snek::update(&world->sneks[i]);
	}
}

void World::draw(WorldState *world) {
	// How large one pixel is
	float scale;
	// Location on the screen for where the world is rendered
	SDL_Rect worldViewport;
	if (global::screenWidth > global::screenHeight) {
		scale = global::screenHeight / WORLD_HEIGHT;
		worldViewport = { (global::screenWidth / 2) - ((WORLD_WIDTH / 2) * scale), 0, WORLD_WIDTH * scale, WORLD_HEIGHT * scale };
	} else {
		scale = global::screenWidth / WORLD_WIDTH;
		worldViewport = { 0, (global::screenHeight / 2) - ((WORLD_HEIGHT / 2) * scale), WORLD_WIDTH * scale, WORLD_HEIGHT * scale };
	}

	// Set the viewport and the scaling for the world
	SDL_RenderSetViewport(global::renderer, &worldViewport);
	SDL_RenderSetScale(global::renderer, scale, scale);

	// Draw all food
	for (size_t i = 0; i < world->numFood; i++) {
		Food::draw(&world->food[i]);
	}

	// Draw all sneks
	for (size_t i = 0; i < world->numSneks; i++) {
		Snek::draw(&world->sneks[i]);
	}

	// Undo the viewport and scaling
	SDL_RenderSetViewport(global::renderer, NULL);
	SDL_RenderSetScale(global::renderer, 1, 1);
}