#include "Game.h"

void Game::init(GameState *game) {
	game->numSneks = 0;
	game->maxFood = 3; // TODO: This should be set by config
}

bool Game::addSnek(GameState *game, SnekState snek) {
	if (game->numSneks < MAX_SNEKS) {
		snek.playerNum = game->numSneks;
		game->sneks[game->numSneks++] = snek;
		return true;
	}

	return false;
}

void Game::reset(GameState *game) {
	// The starting y position of player 1
	int startY = WORLD_HEIGHT / 2 - (((game->numSneks - 1) / 2) * SNEK_START_SPACING) / 2;
	// Initialize snek locations
	for (size_t i = 0; i < game->numSneks; i++) {
		Snek::reset(&game->sneks[i], startY + ((i / 2) * SNEK_START_SPACING), i % 2 == 0);
	}

	// Initialize food locations
	for (size_t i = 0; i < game->maxFood; i++) {
		Game::resetFood(game, i);
	}
}

void Game::resetFood(GameState *game, int foodIdx) {
	Position pos;
	bool flag;
	// Generate a position for the food until it doesn't conflict with a snek
	do {
		pos = { rand() % WORLD_WIDTH, rand() % WORLD_HEIGHT };

		// Check that this position doesn't overlap a snek
		flag = false;
		for (size_t j = 0; j < game->numSneks; j++) {
			if (game->sneks[j].alive && game->sneks[j].body[0].x == pos.x && game->sneks[j].body[0].y == pos.y) {
				flag = true;
				break;
			}
		}
	} while (flag);
	game->food[foodIdx].pos = pos;
}

void Game::update(GameState *game) {
	// Update all sneks in the game
	for (size_t i = 0; i < game->numSneks; i++) {
		if (game->sneks[i].alive) {
			Snek::update(&game->sneks[i]);
		}
	}

	// Check for food collisions
	// Do this first to allow pixel-perfect food-killing strats
	for (size_t i = 0; i < game->maxFood; i++) {
		for (size_t j = 0; j < game->numSneks; j++) {
			// Check for collision of food with head
			if (game->food[i].pos.x == game->sneks[j].body[0].x && game->food[i].pos.y == game->sneks[j].body[0].y) {
				Snek::grow(&game->sneks[j]);
				Game::resetFood(game, i);
				break;
			}
		}
	}

	// Check for snek collisions
	for (size_t i = 0; i < game->numSneks; i++) {
		SnekState *snek1 = &game->sneks[i];

		// Skip dead sneks
		if (!snek1->alive) {
			continue;
		}

		// Check if snek is OOB
		if (snek1->body[0].x < 0 || snek1->body[0].x >= WORLD_WIDTH || snek1->body[0].y < 0 || snek1->body[0].y >= WORLD_HEIGHT) {
			snek1->alive = false;
			continue;
		}

		for (size_t j = i; j < game->numSneks; j++) {
			SnekState *snek2 = &game->sneks[j];

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

void Game::draw(GameState *game, float scale) {
	// Draw all food
	SDL_Color color = FOOD_COLOR;
    SDL_SetRenderDrawColor(global::renderer, color.r, color.g, color.b, color.a);
	for (size_t i = 0; i < game->maxFood; i++) {
		Food::draw(&game->food[i], scale);
	}

	// Draw all sneks
	for (size_t i = 0; i < game->numSneks; i++) {
		if (game->sneks[i].alive) {
			Snek::draw(&game->sneks[i], scale);
		}
	}
}