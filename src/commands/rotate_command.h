#pragma once

#include "command.h"

class RotateCommand : public Command
{
public:
	void execute(Piece& piece, Grid& grid, PlayState& state) final {
		// rotate until a valid rotation is found (this way the user cannot clip out of the wall)
		for (int i = 0; i < 4; i++) {
			piece.m_orientation = (piece.m_orientation + 1) % 4;

			if (grid.collision_check(piece.x(), piece.y(), piece) == Collision::NoCollision)
				break;
		}
	}
};
