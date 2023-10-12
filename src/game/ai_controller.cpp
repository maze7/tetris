#include "ai_controller.h"
#include "commands/move_command.h"
#include "commands/rotate_command.h"

AIController::AIController(PlayState& state, Grid& grid) : m_play_state(state), m_grid(grid) {}

std::unique_ptr<Command> AIController::generate_command(Piece piece) {
	int best_rotation = 0, best_position = 0;
	double best_score = -999999999999;

	for (int r = 0; r < 2; r++) { // for each rotation
		piece.set_rotation(piece.orientation() + r);
		for (int x = 0; x < m_grid.width(); x++) { // for each column
			for (int y = 0; y < m_grid.height(); y++) { // for each row
				Piece p = piece;
				Grid g = m_grid;
				p.set_x(x);
				p.set_y(y);
				p.set_rotation(r);

				if (g.collision_check(p.x(), p.y(), p) == Collision::NoCollision &&
					g.collision_check(p.x(), p.y() + 1, p) == Collision::Blocked) {
					g.place_piece(p);

					double h = heuristic(g);
					if (h > best_score) {
						best_rotation = r;
						best_position = x;
						best_score = h;
					}
				}
			}
		}
	}

	if (piece.x() < best_position)
		return std::make_unique<MoveCommand>(1, 0);
	else if (piece.x() > best_position)
		return std::make_unique<MoveCommand>(-1, 0);
	else if (piece.orientation() != best_rotation)
		return std::make_unique<RotateCommand>();

	return nullptr;
}

double AIController::heuristic(Grid& grid) const {

	const double A = -0.510066;
	const double B = -0.760666;
	const double C = -3.5;
	const double D = 8.0;

	int height_sum = 0;
	// calculate height penalty
	for (int x = 0; x < grid.width(); x++) {
		int y = 0;
		while (y < grid.height() && grid.m_cells[x + y * grid.width()] == -1)
			y++;

		height_sum += m_grid.height() - y;
	}



	// calculate cleared rows
	int clear_sum = grid.clear_rows();

	return A * height_sum
		+  B * clear_sum;
}

AIController::~AIController() {

}

