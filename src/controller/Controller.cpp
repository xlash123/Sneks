#include "Controller.h"

Controller::Controller() {
	type = KEYBOARD;
}

Controller::Controller(SDL_GameController *gamepad) {
	type = GAMEPAD;
	this->gamepad = gamepad;
}

Controller::Controller(int connectionId) {}

PlayerActions Controller::getPlayerActions() {
	return actions;
}

void Controller::updatePlayerActions(SDL_Event *event) {
	switch (type) {
		case KEYBOARD: {
			// Check that the event type is for keyboard events
			if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
				// Mark necesary action as active
				bool isDown = event->type == SDL_KEYDOWN;
				switch (event->key.keysym.scancode) {
					case SDL_SCANCODE_W:
						actions.moveUp = isDown;
						break;
					case SDL_SCANCODE_A:
						actions.moveLeft = isDown;
						break;
					case SDL_SCANCODE_S:
						actions.moveDown = isDown;
						break;
					case SDL_SCANCODE_D:
						actions.moveRight = isDown;
						break;
					default:
				}
			}
			break;
		}
		case GAMEPAD: {

			break;
		}
		case REMOTE: {
			
			break;
		}
	}
}

void Controller::resetPlayerActions() {
	actions = { false, false, false, false, false, false };
}