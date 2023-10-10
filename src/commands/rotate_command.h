#pragma once

#include "command.h"

class RotateCommand : public Command
{
public:
	void execute(Piece& piece, Grid& grid) override {
		piece.m_orientation = (piece.m_orientation + 1) % 4;
	}
};
