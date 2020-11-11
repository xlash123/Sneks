#include "Controller.h"

void Controller::init(ControllerState *controller) {
	Controller::setDefaultActions(controller);
	controller->gamepad = NULL;
	controller->type = NONE;
}

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
			// Make sure we only process this controller
			if (event->cdevice.which != controller->gamepadId) return;
			switch (event->type) {
				// Analog stick movement
				case SDL_JOYAXISMOTION:
					// Determine which axis was moved
					switch (event->caxis.axis) {
						case SDL_CONTROLLER_AXIS_LEFTX:
							controller->actions.moveLeft = event->caxis.value < -CONTROLLER_DEADZONE;
							controller->actions.moveRight = event->caxis.value > CONTROLLER_DEADZONE;
							break;
						case SDL_CONTROLLER_AXIS_LEFTY:
							controller->actions.moveUp = event->caxis.value < -CONTROLLER_DEADZONE;
							controller->actions.moveDown = event->caxis.value > CONTROLLER_DEADZONE;
							break;
						default:;
					}
					break;
				case SDL_JOYHATMOTION:
					// Reset movement options
					controller->actions.moveRight = false;
					controller->actions.moveLeft = false;
					controller->actions.moveUp = false;
					controller->actions.moveDown = false;
					switch (event->jhat.value) {
						case SDL_HAT_UP:
							controller->actions.moveUp = true;
							break;
						case SDL_HAT_DOWN:
							controller->actions.moveDown = true;
							break;
						case SDL_HAT_RIGHTUP:
							controller->actions.moveUp = true;
							controller->actions.moveRight = true;
							break;
						case SDL_HAT_RIGHT:
							controller->actions.moveRight = true;
							break;
						case SDL_HAT_RIGHTDOWN:
							controller->actions.moveRight = true;
							controller->actions.moveDown = true;
							break;
						case SDL_HAT_LEFTUP:
							controller->actions.moveUp = true;
							controller->actions.moveLeft = true;
							break;
						case SDL_HAT_LEFT:
							controller->actions.moveLeft = true;
							break;
						case SDL_HAT_LEFTDOWN:
							controller->actions.moveLeft = true;
							controller->actions.moveDown = true;
							break;
						default:;
					}
			}
			break;
		}
		case REMOTE: {
			
			break;
		}
		default:
			;
	}
}

void Controller::setDefaultActions(ControllerState *controller) {
	controller->actions = { false, false, false, false, false, false };
}