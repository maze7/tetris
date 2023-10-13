#pragma once

#include "play_state.h"

/**
 * The InputSystem is a pure-static singleton which is responsible for generating Commands when the player is in control of the piece.
 */
class InputSystem
{
public:
	/**
	 * Generates a Command which will move the piece based on the current keys that are pressed.
	 * @return A Command which can be executed on the piece
	 */
	static std::unique_ptr<Command> handle_input();
};