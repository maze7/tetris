#pragma once

#include "piece.h"
#include "core/config.h"

class Command
{
public:
	virtual ~Command() = default;

	virtual void execute(Piece& piece) = 0;
};

class MoveCommand : public Command
{
public:
	explicit MoveCommand(int x, int y) : m_x(x), m_y(y) {}

	void execute(Piece& piece) override {
		// only move piece horizontally if the resulting move will not move it off the board
		if ((piece.x() + m_x >= 0) && (piece.x() + piece.width() + m_x <= Config::k_board_width))
			piece.m_x += m_x;

		piece.m_y += m_y;
	}

private:
	int m_x, m_y;
};

class RotateCommand : public Command
{
public:
	void execute(Piece& piece) override {
		piece.m_orientation = (piece.m_orientation + 1) % 4;
	}
};

