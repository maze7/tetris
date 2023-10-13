#pragma once

#include "command.h"

/**
 * RotateCommand rotates a given piece in the board
 */
class RotateCommand : public Command
{
public:
	/**
	 * Attempts to rotate the provided piece until a vaild position is found, or the piece has returned to its original orientation
	 * @param piece The piece to be rotated
	 * @param grid The grid the piece exists in
	 * @param state The current play state
	 */
	void execute(Piece& piece, Grid& grid, PlayState& state) final {
		// rotate until a valid rotation is found (this way the user cannot clip out of the wall)
		for (int i = 0; i < 4; i++) {
			piece.m_orientation = (piece.m_orientation + 1) % 4;

			if (grid.collision_check(piece.x(), piece.y(), piece) == Collision::NoCollision)
				break;
		}
	}
};
