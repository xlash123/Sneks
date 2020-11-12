#include "World.h"

void World::init(WorldState *world) {
	world->numSneks = 0;
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

	// Initialize food locations
	for (size_t i = 0; i < world->maxFood; i++) {
		World::resetFood(world, i);
	}
}

void World::resetFood(WorldState *world, int foodIdx) {
	Position pos;
	bool flag;
	// Generate a position for the food until it doesn't conflict with a snek
	do {
		pos = { rand() % WORLD_WIDTH, rand() % WORLD_HEIGHT };

		// Check that this position doesn't overlap a snek
		flag = false;
		for (size_t j = 0; j < world->numSneks; j++) {
			if (world->sneks[j].alive && world->sneks[j].body[0].x == pos.x && world->sneks[j].body[0].y == pos.y) {
				flag = true;
				break;
			}
		}
	} while (flag);
	world->food[foodIdx].pos = pos;
}

void World::update(WorldState *world) {
	// Update all sneks in the world
	for (size_t i = 0; i < world->numSneks; i++) {
		if (world->sneks[i].alive) {
			Snek::update(&world->sneks[i]);
		}
	}

	// Check for food collisions
	// Do this first to allow pixel-perfect food-killing strats
	for (size_t i = 0; i < world->maxFood; i++) {
		for (size_t j = 0; j < world->numSneks; j++) {
			// Check for collision of food with head
			if (world->food[i].pos.x == world->sneks[j].body[0].x && world->food[i].pos.y == world->sneks[j].body[0].y) {
				Snek::grow(&world->sneks[j]);
				World::resetFood(world, i);
				break;
			}
		}
	}


	// Check for snek collisions
	for (size_t i = 0; i < world->numSneks; i++) {
		SnekState *snek1 = &world->sneks[i];

		// Skip dead sneks
		if (!snek1->alive) {
			continue;
		}

		// Check if snek is OOB
		if (snek1->body[0].x < 0 || snek1->body[0].x >= WORLD_WIDTH || snek1->body[0].y < 0 || snek1->body[0].y >= WORLD_HEIGHT) {
			snek1->alive = false;
			continue;
		}

		for (size_t j = i; j < world->numSneks; j++) {
			SnekState *snek2 = &world->sneks[j];

			// Skip dead sneks
			if (!snek2->alive) {
				continue;
			}
			
			for (size_t b = 0; b < snek2->length; b++) {
				// Don't check for head collision for the same snek
				if (b == 0 && i == j) {
					continue;
				}
				// If the snek intersects with another's body
				if (snek1->body[0].x == snek2->body[b].x && snek1->body[0].y == snek2->body[b].y) {
					// If their heads are colliding, kill both
					if (b == 0) {
						snek2->alive = false;
					}
					snek1->alive = false;
					// Break to snek2 loop since snek1 is now dead
					goto Snek2_Loop;
				}
			}
		}
		Snek2_Loop:;
	}
}

void World::draw(WorldState *world, float scale) {
	// Draw all food
	SDL_Color color = FOOD_COLOR;
    SDL_SetRenderDrawColor(global::renderer, color.r, color.g, color.b, color.a);
	for (size_t i = 0; i < world->maxFood; i++) {
		Food::draw(&world->food[i], scale);
	}

	// Draw all sneks
	for (size_t i = 0; i < world->numSneks; i++) {
		if (world->sneks[i].alive) {
			Snek::draw(&world->sneks[i], scale);
		}
	}
}