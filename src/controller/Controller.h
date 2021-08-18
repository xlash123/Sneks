#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <SDL2/SDL.h>

#include "../snek/Snek.h"

#define CONTROLLER_DEADZONE ((int) (0.5 * 32767))
#define CONTROLLER_MAX_INPUTS SDL_CONTROLLER_BUTTON_MAX + SDL_CONTROLLER_AXIS_MAX

// The type of controller to get inputs from
typedef enum {
	NONE, KEYBOARD, GAMEPAD, REMOTE
} ControllerType;

typedef enum {
	BUTTON, AXIS
} InputType;

// Defines an input
typedef struct {
	InputType type;
	// The index of that button
	int index;
} Input;

// The default mapping of inputs. Used as reference for what actions do what, or to reset bindings
Input defaultInputBindings[CONTROLLER_MAX_INPUTS];

// Controller metadata
typedef struct {
	// The type of controller
	ControllerType type;
	// The configured input bindings
	Input inputBindings[CONTROLLER_MAX_INPUTS];
	// The buttons that are pressed
	bool buttons[SDL_CONTROLLER_BUTTON_MAX];
	// The state of each axis
	int axis[SDL_CONTROLLER_AXIS_MAX];
} ControllerState;

namespace Controller {
	// Initialize controller state
	void init(ControllerState *controller);

	void updateController(ControllerState *controller, SDL_Event *event);

	// Update that controller based on SDL events
	void updateActions(ControllerState *controller, SnekState *snek);
};

void createDefaultInputBindings();

#endif