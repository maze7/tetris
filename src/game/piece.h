#pragma once

#include "piece_definitions.h"

// forward declare commands that can act upon a piece
class MoveCommand;
class RotateCommand;
class Piece
{
public:
	Piece() = default;

	// current piece position
	[[nodiscard]] int x() const { return m_x; }
	[[nodiscard]] int y() const { return m_y; }

	// current piece width & height
	[[nodiscard]] int width() const { return s_pieces[m_piece_id].width[m_orientation]; }
	[[nodiscard]] int height() const { return s_pieces[m_piece_id].height[m_orientation]; }

	// Current piece color
	[[nodiscard]] Color color() const { return s_pieces[m_piece_id].color; }

	// reset and start a new piece falling
	//void next_piece(int piece_id);

	// draw the current piece to the board
	void draw(int offset_x, int offset_y);

	static constexpr int k_block_size = 32;

private:
	int m_x 			= 4;
	int m_y 			= -1;
	int m_orientation 	= 0;
	int m_piece_id 		= 1;

	friend class MoveCommand;
	friend class RotateCommand;
};
