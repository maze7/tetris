#pragma once

#include "command.h"

class MoveCommand : public Command
{
public:
	explicit MoveCommand(int x, int y) : m_x(x), m_y(y) {}

	void execute(Piece& piece, Grid& grid) final;

private:
	int m_x, m_y;
};