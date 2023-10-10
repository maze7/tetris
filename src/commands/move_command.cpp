#include <bitset>
#include "move_command.h"
#include "game/play_state.h"
#include "core/game.h"

void MoveCommand::execute(Piece& piece, Grid& grid, PlayState& state) {
	int nx = piece.m_x + m_x, ny = piece.m_y + m_y;

	// only move piece horizontally if the resulting move will not move it off the board
	auto collision = grid.collision_check(nx, ny, piece);

	// if the piece will move to the floor or a piece is blocking it horizontally, place the piece in the grid
	if (collision & Collision::Floor || collision & Collision::PieceDown) {
		grid.place_piece(piece.m_x, piece.m_y, piece);
		piece.next_piece((grid.width() / 2) - (piece.width()/2), 0, rand() % state.num_game_pieces());
	}

	// check for game over condition
	if (grid.collision_check(piece.x(), piece.y(), piece) != Collision::NoCollision) {
		state.game_over();
	}

	// if the piece hasn't collided with anything, allow the move
	if (collision == Collision::NoCollision) {
		piece.m_x = nx;
		piece.m_y = ny;
	}
}