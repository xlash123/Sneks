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
} PlayerActions;

// A collection of action bindings for every snek action for configuration
typedef struct {
	// Directional movements
	ActionBinding moveUp, moveDown, moveLeft, moveRight;
	// Minor speed boosts
	ActionBinding speedUp, speedDown;
} ActionBindings;

// Interface by which a Snek can be controlled. This can represent the player, a server, or a computer
class Controller {
private:
	// The actions that the snek will make in the next frame
	PlayerActions actions;

	// The type of controller the player is using
	ControllerType type;

	// Reference to the underlying SDL Controller (used only for type = GAMEPAD)
	SDL_GameController *gamepad;
public:
	// Create new keyboard-based controller
	Controller();
	// Create a new controller for a given gamepad
	Controller(SDL_GameController *gamepad);
	// Create a new controller for a remove player. TODO: Replace connectionId with a real identifier
	Controller(int connectionId);

	// Returns the actions the player makes in the current frame
	PlayerActions getPlayerActions();

	// Polls for the input of the user
	void updatePlayerActions(SDL_Event *event);

	// Reset the player actions to nothing pressed
	void resetPlayerActions();
};

#endif