#pragma once

#include "play_state.h"

class AIController
{
public:
	AIController(PlayState& state, Grid& grid);

	std::unique_ptr<Command> generate_move();

private:
	PlayState& 	m_play_state;
	Grid& 		m_grid;
};