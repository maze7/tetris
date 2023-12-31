#pragma once

#include "command.h"


class DropCommand : public Command
{
public:
	/**
	 * Drops the piece at the current x position. The piece will fall until it is blocked by a piece below it or the floor
	 * @param piece The piece to be blocked
	 * @param grid The grid the piece exists in
	 * @param state The current play state
	 */
	void execute(Piece& piece, Grid& grid, PlayState& state) final {
		// simulate moving piece to the lowest possible location with current x position & rotation
		while (!(grid.collision_check(piece.x(), piece.y() + 1, piece) & Collision::Blocked))
			piece.m_y += 1;

		// place the piece on the board
		grid.place_piece(piece);
		piece.next_piece((grid.width() / 2) - (piece.width()/2), 0, state.next_piece());
		state.set_next_piece(rand() % state.num_game_pieces());

		// clear and completed rows and earn points
		auto rows_cleared = grid.clear_rows();
		state.set_score(state.score() + PlayState::k_points_lookup[std::min(rows_cleared, 4)]);
		state.set_rows_cleared(state.rows_cleared() + rows_cleared);
	}
};