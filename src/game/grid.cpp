#include "grid.h"

Grid::Grid(int width, int height): m_width(width), m_height(height) {
	m_cells = new int[m_width * m_height];
	// fill all cells as empty to begin
	for (int i = 0; i < m_width * m_height; i++)
		m_cells[i] = -1;
}

Grid::~Grid() {
	delete[] m_cells;
}

void Grid::draw(int x, int y) const {
	int left = x;
	int right = x + (m_width * k_cell_size);
	int top = y;
	int bottom = y + (m_height * k_cell_size);

	// Grid Outline
	DrawRectangle(left, top, right-left + (2*k_border_width), bottom-top + (2*k_border_width), GRAY);
	DrawRectangle(left + k_border_width, top + k_border_width, right-left, bottom-top, BLACK);

	// Draw squares
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			if (m_cells[i + j * m_width] != -1)
				DrawRectangle(left + (i * 32) + k_border_width, top + (j * 32) + k_border_width, 32, 32, s_pieces[m_cells[i + j * m_width]].color);
		}
	}

	// Draw vertical grid lines
	for (int i = 1; i < m_width; i++) {
		DrawLine((left + k_border_width) + (i * 32), top + k_border_width, (left + k_border_width) + (i * 32), bottom + 4, DARKGRAY);
	}

	// Draw horizontal grid lines
	for (int i = 1; i < m_height; i++) {
		DrawLine(left + k_border_width, top + k_border_width + (i * 32), right + 4, top + k_border_width + (i * 32), DARKGRAY);
	}
}

int Grid::collides(int x, int y, Piece& piece) const {

	auto layout = piece.layout();
	int result = Collision::NoCollision;

	for (int dx = 0; dx < piece.width(); dx++) {
		for (int dy = 0; dy < piece.height(); dy++) {
			if (layout[dx + dy * 4]) {
				// horizontal bounds check
				if ((dx + x < 0) || (dx + x >= m_width))
					result |= Collision::Wall;

				// vertical bounds check
				if (dy + y >= m_height)
					result |= Collision::Floor;

				// other pieces check
				if (m_cells[(dx + x) + (dy + y) * m_width] != -1) {
					if (x < piece.x())
						result |= Collision::PieceLeft;
					if (x > piece.x())
						result |= Collision::PieceRight;
					if (y > piece.y())
						result |= Collision::PieceDown;

					std::cout << "Piece collision: (local: " << dx << "," << dy << "), (grid: " << dx + x << "," << dy + y << ")" << std::endl;
				}
			}
		}
	}

	return result;
}

void Grid::place_piece(int x, int y, Piece& piece) const {
	for (int dx = 0; dx < piece.width(); dx++) {
		for (int dy = 0; dy < piece.height(); dy++) {
			if (piece.layout()[dx + dy * 4]) {
				m_cells[(dx + x) + (dy + y) * m_width] = piece.current_piece_id();
			}
		}
	}
}