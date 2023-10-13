#pragma once

#include <memory>
#include "piece.h"
#include "commands/command.h"

class Grid;
class Command;
class Piece;
class PlayState;
class AIController
{
public:
	struct AIResult {
		Piece target;
		std::unique_ptr<Command> command;
	};

	AIController(PlayState& state, Grid& grid);
	~AIController();

	AIResult generate_command(Piece piece);

private:
	double heuristic(Grid&) const;

	PlayState& 	m_play_state;
	Grid& 		m_grid;
};