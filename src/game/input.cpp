#include "pch.h"
#include "input.h"
#include "commands/move_command.h"
#include "commands/rotate_command.h"

std::unique_ptr<Command> InputSystem::handle_input() {
	// rotate block clockwise
	if (IsKeyPressed(KEY_UP)) {
		return std::make_unique<RotateCommand>();
	}

	// move block left / right
	if (IsKeyPressed(KEY_LEFT)) {
		return std::make_unique<MoveCommand>(-1, 0);
	} 
	else if (IsKeyPressed(KEY_RIGHT)) {
		return std::make_unique<MoveCommand>(1, 0);
	}
	else if (IsKeyPressed(KEY_DOWN)) {
		return std::make_unique<MoveCommand>(0, 1);
	}

	return nullptr;
}


