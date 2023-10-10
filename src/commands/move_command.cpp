#include <bitset>
#include "move_command.h"
#include "game/play_state.h"
#include "core/game.h"

void MoveCommand::execute(Piece& piece, Grid& grid) {
	int nx = piece.m_x + m_x, ny = piece.m_y + m_y;

	// only move piece horizontally if the resulting move will not move it off the board
	auto collision = grid.collides(nx, ny, piece);

	std::bitset<8> bits(collision);
	std::cout << "Collision: " << bits << std::endl;

	if (collision == Collision::NoCollision) {
		piece.m_x = nx;
		piece.m_y = ny;
	}

	// if the piece will move to the floor or a piece is blocking it horizontally, place the piece in the grid
	if (collision & Collision::Floor || collision & Collision::PieceDown) {
		grid.place_piece(piece.m_x, piece.m_y, piece);
		piece.next_piece(rand() % 7);
	}
}