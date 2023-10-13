#pragma once

#include "command.h"

/**
 * MoveCommand inherits from the Command class, and implements a simple piece move command.
 */
class MoveCommand : public Command
{
public:
	explicit MoveCommand(int x, int y) : m_x(x), m_y(y) {}

	/**
	 * Attempts to move the piece by a certain amount on the x and y axes
	 * @param piece the piece to be moved
	 * @param grid the grid the piece is moving in
	 * @param state the current game state
	 */
	void execute(Piece& piece, Grid& grid, PlayState& state) final;

private:
	int m_x;
	int m_y;
};