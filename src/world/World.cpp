#include "World.h"

void World::init(WorldState *world) {
	world->numSneks = 0;
	world->numFood = 0;
	world->maxFood = 3; // TODO: This should be set by config
}

bool World::addSnek(WorldState *world, SnekState snek) {
	if (world->numSneks < MAX_SNEKS) {
		snek.playerNum = world->numSneks;
		world->sneks[world->numSneks++] = snek;
		return true;
	}

	return false;
}

void World::reset(WorldState *world) {
	// The starting y position of player 1
	int startY = WORLD_HEIGHT / 2 - (((world->numSneks - 1) / 2) * SNEK_START_SPACING) / 2;
	// Initialize snek locations
	for (size_t i = 0; i < world->numSneks; i++) {
		Snek::reset(&world->sneks[i], startY + ((i / 2) * SNEK_START_SPACING), i % 2 == 0);
	}
}

void World::update(WorldState *world) {
	// Update all sneks in the world
	for (size_t i = 0; i < world->numSneks; i++) {
		Snek::update(&world->sneks[i]);
	}
}

void World::draw(WorldState *world, float scale) {
	// Draw all food
	for (size_t i = 0; i < world->numFood; i++) {
		Food::draw(&world->food[i]);
	}

	// Draw all sneks
	for (size_t i = 0; i < world->numSneks; i++) {
		Snek::draw(&world->sneks[i], (int) scale);
	}
}