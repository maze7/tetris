#include "ai_controller.h"
#include "game/play_state.h"
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
			if (temp_grid.collision_check(temp_piece.x(), temp_piece.y(), temp_piece) != Collision::NoCollision)
				continue;

			// ensure goal position is accessible
			Piece move_check = temp_piece;
			while (temp_grid.collision_check(move_check.x(), move_check.y(), move_check) != Collision::NoCollision) {
				if (move_check.x() < x)
					move_check.set_x(move_check.x() + 1);
				else if (move_check.x() > x)
					move_check.set_x(move_check.x() - 1);
			}

			if (move_check.x() != x)
				continue;

			// simulate moving piece to the lowest possible location with current x position & rotation
			while (!(temp_grid.collision_check(temp_piece.x(), temp_piece.y() + 1, temp_piece) & Collision::Blocked))
				temp_piece.set_y(temp_piece.y() + 1);

			// place the temp piece in the temp grid
			temp_grid.place_piece(temp_piece);

			for (int r_next = 0; r_next < 4; r_next++) {
				for (int x_next = 0; x_next < m_grid.width(); x_next++) {
					Grid next_temp_grid = temp_grid; // copy grid so we can generate a dummy solution
					Piece next_temp_piece = Piece(m_grid.width()/2, 0, m_play_state.m_next_piece_id);

					next_temp_piece.set_rotation(r_next); // move piece to current rotation
					next_temp_piece.set_x(x_next); // move piece to current x value

					// if this move will clip outside the board, skip it
					if (next_temp_grid.collision_check(next_temp_piece.x(), next_temp_piece.y(), next_temp_piece) != Collision::NoCollision)
						continue;

					// ensure goal position is accessible
					Piece next_move_check = next_temp_piece;
					while (next_temp_grid.collision_check(next_move_check.x(), next_move_check.y(), next_move_check) != Collision::NoCollision) {
						if (next_move_check.x() < x_next)
							next_move_check.set_x(next_move_check.x() + 1);
						else if (next_move_check.x() > x_next)
							next_move_check.set_x(next_move_check.x() - 1);
					}

					if (next_move_check.x() != x_next)
						continue;

					// simulate moving piece to the lowest possible location with current x position & rotation
					while (!(next_temp_grid.collision_check(next_temp_piece.x(), next_temp_piece.y() + 1, next_temp_piece) & Collision::Blocked))
						next_temp_piece.set_y(next_temp_piece.y() + 1);

					// place the temp piece in the temp grid
					next_temp_grid.place_piece(next_temp_piece);

					// evaluate the resulting grid
					double h = heuristic(next_temp_grid);

					if (h > best_eval) {
						best_r = r;
						best_x = x;
						best_eval = h;
					}
				}
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

	// calculate number of pieces touching floor
	int floor_pieces = 0;
	for (int x = 0; x < grid.width(); x++)
		floor_pieces += grid.m_cells[x + (grid.height()-1) * grid.width()] == -1 ? 0 : 1;

	// calculate number of pieces touching walls
	int wall_pieces = 0;
	for (int y = 0; y < grid.height(); y++) {
		wall_pieces += grid.m_cells[0 + y * grid.width()] == -1 ? 0 : 1;
		wall_pieces += grid.m_cells[(grid.width()-1) * y + grid.width()] == -1 ? 0 : 1;
	}

	// calculate sum of edges
	auto is_occupied = [&](int ix, int iy) {
		return ix >= 0 && ix < grid.width() && iy >= 0 && iy < grid.height() && grid.cell_value(ix, iy) != -1;
	};

	int edge_sum = 0;
	for (int x = 0; x < grid.width(); x++) {
		for (int y = 0; y < grid.height(); y++) {
			if (is_occupied(x, y)) {
				if (is_occupied(x, y-1)) edge_sum++;
				if (is_occupied(x + 1, y)) edge_sum++;
				if (is_occupied(x, y + 1)) edge_sum++;
				if (is_occupied(x - 1, y)) edge_sum++;
			}
		}
	}

	const double A = -17.78;
	const double B = 32.0;
	const double C = -0.22;
	const double D = -0.011;
	const double E = 1.85;
	const double F = 0.32;
	const double G = 0.37;

	return A * height_sum
		+  B * clear_sum
		+  C * holes_sum
		+  D * blockades_sum
		+  E * floor_pieces
		+  F * wall_pieces
		+  G * edge_sum;
}

AIController::~AIController() {

}
