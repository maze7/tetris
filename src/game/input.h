#pragma once

#include "play_state.h"

class InputSystem
{
public:
	static std::unique_ptr<Command> handle_input();
};