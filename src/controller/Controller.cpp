#include "Controller.h"

void Controller::updateActions(ControllerState *controller, SDL_Event *event) {
	switch (controller->type) {
		case KEYBOARD: {
			// Check that the event type is for keyboard events
			if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
				// Mark necesary action as active
				bool isDown = event->type == SDL_KEYDOWN;
				switch (event->key.keysym.scancode) {
					case SDL_SCANCODE_W:
						controller->actions.moveUp = isDown;
						break;
					case SDL_SCANCODE_A:
						controller->actions.moveLeft = isDown;
						break;
					case SDL_SCANCODE_S:
						controller->actions.moveDown = isDown;
						break;
					case SDL_SCANCODE_D:
						controller->actions.moveRight = isDown;
						break;
					default:
						;
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

void Controller::setDefaultActions(ControllerState *controller) {
	controller->actions = { false, false, false, false, false, false };
}