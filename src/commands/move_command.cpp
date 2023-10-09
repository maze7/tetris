#include "move_command.h"
#include "game/play_state.h"
#include "core/game.h"

void MoveCommand::execute(Piece& piece, PlayState& ps) {
	// only move piece horizontally if the resulting move will not move it off the board
	if ((piece.x() + m_x >= 0) && (piece.x() + piece.width() + m_x <= ps.game()->config().board_width))
	piece.m_x += m_x;

	piece.m_y += m_y;
}