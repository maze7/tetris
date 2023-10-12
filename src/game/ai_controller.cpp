#include "ai_controller.h"

AIController::AIController(PlayState& state, Grid& grid) : m_play_state(state), m_grid(grid) {}

std::unique_ptr<Command> AIController::generate_move() {
	//

	return std::unique_ptr<Command>();
}

