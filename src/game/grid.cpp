#include "grid.h"

Grid::Grid(int width, int height): m_width(width), m_height(height) {
	m_cells.resize(m_width * m_height);

	for (int i = 0; i < m_width * m_height; i++)
		m_cells[i] = -1;
}

void Grid::draw(int x, int y, Texture& block, Piece piece) const {
	int left = x;
	int right = x + (m_width * k_cell_size) + m_width + m_width;
	int top = y;
	int bottom = y + (m_height * k_cell_size) + m_height + m_height;

	// Grid background
	DrawRectangle(left, top, right-left, bottom-top, Color(18, 20, 61, 255));

	// Draw squares
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			if (m_cells[i + j * m_width] != -1)
				DrawTexture(block,
							x + (i * Piece::k_block_size) + (i*2),
							y + (j * Piece::k_block_size) + (j*2),
							s_pieces[m_cells[i + j * m_width]].color);
		}
	}

	// simulate moving piece to the lowest possible location with current x position & rotation
	while (!(collision_check(piece.x(), piece.y() + 1, piece) & Collision::Blocked))
		piece.set_y(piece.y() + 1);

	// draw the piece with lowered opacity
	piece.draw(x, y, block, 25);
}

int Grid::collision_check(int x, int y, Piece& piece) const {

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
				if ((dx + x) < m_width && (dy + y) < m_height) {
					if (m_cells[(dx + x) + (dy + y) * m_width] != -1) {
						if (x < piece.x())
							result |= Collision::PieceLeft;
						else if (x > piece.x())
							result |= Collision::PieceRight;
						else if (y > piece.y())
							result |= Collision::PieceDown;
						else
							result |= Collision::PieceCollision;
					}
				}
			}
		}
	}

	return result;
}

void Grid::place_piece(Piece& piece) {
	for (int dx = 0; dx < piece.width(); dx++) {
		for (int dy = 0; dy < piece.height(); dy++) {
			if (piece.layout()[dx + dy * 4]) {
				if ((dx + piece.x()) < m_width && (dy + piece.y()) < m_height)
					m_cells[(dx + piece.x()) + (dy + piece.y()) * m_width] = piece.current_piece_id();
			}
		}
	}
}

int Grid::clear_rows() {
	int num_cleared = 0;
	std::vector<int> marked_rows;

	// check if any rows can be cleared
	for (int y = m_height - 1; y >= 0; y--) {
		int total = 0;

		// check each cell in the row
		for (int x = 0; x < m_width; x++)
			if (m_cells[x + y * m_width] >= 0) total++;

		// if all cells are full, clear the row
		if (total == m_width) {
			marked_rows.push_back(y);
		}
	}

	// clear marked rows and shift rows above downward
	for (int i = marked_rows.size() - 1; i >= 0; i--) {
		int row = marked_rows[i];
		for (int y = row; y > 0; y--) {
			for (int x = 0; x < m_width; x++)
				m_cells[x + y * m_width] = m_cells[x + (y-1) * m_width];
		}
		num_cleared++;
	}

	// Clear the topmost rows based on how many rows were cleared
	for (int i = 0; i < num_cleared; i++) {
		for (int x = 0; x < m_width; x++)
			m_cells[x + i * m_width] = -1;
	}

	return num_cleared;
}

bool Grid::top_row_clear() const {
	for (int i = 0; i < width(); i++)
		if (m_cells[i] != -1)
			return false;

	return true;
}
