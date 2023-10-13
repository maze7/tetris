#pragma once

#include <game/grid.h>

class PlayState;

/**
 * The command class acts as an abstract interface from which commands can be implemented
 */
class Command
{
public:
	virtual ~Command() = default;

	/**
	 * Executes a given command with the respective piece, grid & game state
	 * @param piece
	 * @param grid
	 * @param state
	 */
	virtual void execute(Piece& piece, Grid& grid, PlayState& state) = 0;
};