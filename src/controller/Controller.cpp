#include "Controller.h"

void createDefaultInputBindings() {
	int i;
	for (i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
		defaultInputBindings[i] = { BUTTON, i };
	}
	for (i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++) {
		defaultInputBindings[i + SDL_CONTROLLER_BUTTON_MAX] = { AXIS, i };
	}
}

void Controller::init(ControllerState *controller) {
	controller->type = NONE;
}

void Controller::updateController(ControllerState *controller, SDL_Event *event) {

}

void Controller::updateActions(ControllerState *controller, SnekState *snek) {
	switch (controller->type) {
		case KEYBOARD: {
			// Check that the event type is for keyboard events
			if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
				// Mark necesary action as active
				bool isDown = event->type == SDL_KEYDOWN;
				switch (event->key.keysym.scancode) {
					case SDL_SCANCODE_W:
						snek->actions.moveUp = isDown;
						break;
					case SDL_SCANCODE_A:
						snek->actions.moveLeft = isDown;
						break;
					case SDL_SCANCODE_S:
						snek->actions.moveDown = isDown;
						break;
					case SDL_SCANCODE_D:
						snek->actions.moveRight = isDown;
						break;
					default:;
				}
			}
			break;
		}
		case GAMEPAD: {
			// Make sure we only process this controller
			if (event->cdevice.which != controller->gamepadId) return;
			switch (event->type) {
				// Analog stick movement
				case SDL_JOYAXISMOTION:
					// Determine which axis was moved
					switch (event->caxis.axis) {
						case SDL_CONTROLLER_AXIS_LEFTX:
							snek->actions.moveLeft = event->caxis.value < -CONTROLLER_DEADZONE;
							snek->actions.moveRight = event->caxis.value > CONTROLLER_DEADZONE;
							break;
						case SDL_CONTROLLER_AXIS_LEFTY:
							snek->actions.moveUp = event->caxis.value < -CONTROLLER_DEADZONE;
							snek->actions.moveDown = event->caxis.value > CONTROLLER_DEADZONE;
							break;
						default:;
					}
					break;
				case SDL_JOYHATMOTION:
					// Reset movement options
					snek->actions.moveRight = false;
					snek->actions.moveLeft = false;
					snek->actions.moveUp = false;
					snek->actions.moveDown = false;
					switch (event->jhat.value) {
						case SDL_HAT_UP:
							snek->actions.moveUp = true;
							break;
						case SDL_HAT_DOWN:
							snek->actions.moveDown = true;
							break;
						case SDL_HAT_RIGHTUP:
							snek->actions.moveUp = true;
							snek->actions.moveRight = true;
							break;
						case SDL_HAT_RIGHT:
							snek->actions.moveRight = true;
							break;
						case SDL_HAT_RIGHTDOWN:
							snek->actions.moveRight = true;
							snek->actions.moveDown = true;
							break;
						case SDL_HAT_LEFTUP:
							snek->actions.moveUp = true;
							snek->actions.moveLeft = true;
							break;
						case SDL_HAT_LEFT:
							snek->actions.moveLeft = true;
							break;
						case SDL_HAT_LEFTDOWN:
							snek->actions.moveLeft = true;
							snek->actions.moveDown = true;
							break;
						default:;
					}
			}
			break;
		}
		case REMOTE: {
			
			break;
		}
		default:;
	}
}
