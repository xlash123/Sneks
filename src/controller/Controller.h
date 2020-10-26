#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <SDL2/SDL.h>

// The type of controller to get inputs from
typedef enum {
	KEYBOARD, GAMEPAD, REMOTE
} ControllerType;

// The index and value of a hat input
typedef struct {
	Uint8 index;
	Uint8 value;
} JoystickHatBinding;

// The index and value of an axis input
typedef struct {
	Uint8 index;
	Sint16 value;
} JoystickAxisBinding;

// The definition of a single action binding
typedef union {
	// A keyboard input
	SDL_Scancode keycode;

	// A joystick button input
	Uint8 joystickButton;
	// A joystick hat - hi = index, lo = value
	JoystickHatBinding joystickHat;
	JoystickAxisBinding joystickAxis;
} ActionBinding;

// The actions the player has shown intent to perform
typedef struct {
	// Directional movements
	bool moveUp, moveDown, moveLeft, moveRight;
	// Minor speed boosts
	bool speedUp, speedDown;
} Actions;

// A collection of action bindings for every snek action for configuration
typedef struct {
	// Directional movements
	ActionBinding moveUp, moveDown, moveLeft, moveRight;
	// Minor speed boosts
	ActionBinding speedUp, speedDown;
} ActionBindings;

typedef struct {
	// The actions of the player made by this controller
	Actions actions;
	// The type of controller
	ControllerType type;
	// Reference to the underlying SDL Controller (used only for type = GAMEPAD)
	SDL_GameController *gamepad;
} ControllerState;

namespace Controller {
	// Set an SDL gamepad to a controller
	void setGamepad(ControllerState *controller, SDL_GameController *gamepad);
	// Set the actions of the controller to the default
	void setDefaultActions(ControllerState *controller);
	// Update that controller based on SDL events
	void updateActions(ControllerState *controller, SDL_Event *event);
};

#endif