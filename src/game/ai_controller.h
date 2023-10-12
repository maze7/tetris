#pragma once

class Grid;
class Command;
class Piece;
class PlayState;
class AIController
{
public:
	AIController(PlayState& state, Grid& grid);
	~AIController();

	std::unique_ptr<Command> generate_command(Piece piece);

private:
	double heuristic(Grid&) const;

	PlayState& 	m_play_state;
	Grid& 		m_grid;
};