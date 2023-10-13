#pragma once

#include <memory>
#include "piece.h"
#include "commands/command.h"

class Grid;
class Command;
class Piece;
class PlayState;

/**
 * The AIController is responsible for generating Commands when the game is in the AI GameMode. The AIController uses a hedonistic
 * search to determine the best possible move when considering the current and next piece.
 */
class AIController
{
public:
	/**
	 * Struct used to represent a "Goal" position and the next command to get there. The target piece is used to draw where the AI is
	 * planning on moving the piece to. The command is the next command that should be executed to get there.
	 */
	struct AIResult {
		Piece target;
		std::unique_ptr<Command> command;
	};

	/**
	 * The AI Controller constructor does nothing. It only stores the state & grid for later use.
	 * @param state reference to the current PlayState
	 * @param grid reference to the current Grid
	 */
	AIController(PlayState& state, Grid& grid);

	/**
	 * Uses a greedy local search algorithm to determine the best possible move, by combining the current piece and the next piece.
	 * Returns an AIResult struct which contains the target location as well as the next command to move the piece to the target location.
	 * @param piece The piece that should be moved
	 * @return AIResult containing target and command
	 */
	AIResult generate_command(Piece piece);

private:
	/**
	 * The heuristic is the algorithm used to determine the quality of a given move. The heuristic factors in many variables, such as
	 * the sum of block heights, the number of gaps in the grid, how many gaps are 'blocked' from being filled, how many blocks have another
	 * adjacent block, and whether the move will result in a clear.
	 * @return Returns a 'quality' value of the move, calculated using weights.
	 */
	double heuristic(Grid&) const;

	PlayState& 	m_play_state;
	Grid& 		m_grid;
};