#include "ai_controller.h"
#include "commands/move_command.h"
#include "commands/rotate_command.h"

AIController::AIController(PlayState& state, Grid& grid) : m_play_state(state), m_grid(grid) {}

AIController::AIResult AIController::generate_command(Piece piece) {
	int best_r = 0, best_x = 0;
	double best_eval = -999999999999;

	for (int r = 0; r < 4; r++) { // for each rotation
		for (int x = 0; x < m_grid.width(); x++) { // for each column
			Grid temp_grid = m_grid; // copy grid so we can generate a dummy solution
			Piece temp_piece = piece; // copy piece so we can generate a dummy solution

			temp_piece.set_rotation(r); // move piece to current rotation
			temp_piece.set_x(x); // move piece to current x value

			// if this move will clip outside the board, skip it
			if (temp_piece.x() + temp_piece.width() >= m_grid.width())
				continue;

			// simulate moving piece to the lowest possible location with current x position & rotation
			while (!(temp_grid.collision_check(temp_piece.x(), temp_piece.y() + 1, temp_piece) & Collision::Blocked))
				temp_piece.set_y(temp_piece.y() + 1);

			// place the temp piece in the temp grid
			temp_grid.place_piece(temp_piece);

			// evaluate the resulting grid
			double h = heuristic(temp_grid);

			if (h > best_eval) {
				best_r = r;
				best_x = x;
				best_eval = h;
			}
		}
	}

	Piece goal_piece = piece;
	// generate target piece location
	goal_piece.set_x(best_x);
	goal_piece.set_rotation(best_r);

	if (piece.orientation() != best_r)
		return { goal_piece, std::make_unique<RotateCommand>() };

	if (piece.x() < best_x)
		return { goal_piece, std::make_unique<MoveCommand>(1, 0) };
	else if (piece.x() > best_x)
		return { goal_piece, std::make_unique<MoveCommand>(-1, 0) };

	return { goal_piece, std::make_unique<MoveCommand>(0, 1) };
}

double AIController::heuristic(Grid& grid) const {

	const double A = -50.03;
	const double B = 8.0;
	const double C = -2.31;
	const double D = -4.59;

	int height_sum = 0;
	// calculate height penalty
	for (int x = 0; x < grid.width(); x++) {
		int y = 0;
		while (y < grid.height() && grid.m_cells[x + y * grid.width()] == -1)
			y++;

		height_sum += grid.height() - y;
	}

	// calculate cleared rows
	int clear_sum = grid.clear_rows();

	// calculate holes
	int holes_sum = 0;
	for (int x = 0; x < grid.width(); x++)
		holes_sum += grid.count_holes(x);

	// calculate blockades
	int blockades_sum = 0;
	for (int x = 0; x < grid.width(); x++)
		blockades_sum += grid.count_holes(x) > 0 ? 1 : 0;

	return A * height_sum
		+  B * clear_sum
		+  C * holes_sum
		+  D * blockades_sum;
}

AIController::~AIController() {

}
