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
	// Draw all food
	for (size_t i = 0; i < world->numFood; i++) {
		Food::draw(&world->food[i]);
	}

	// Draw all sneks
	for (size_t i = 0; i < world->numSneks; i++) {
		Snek::draw(&world->sneks[i]);
	}
}