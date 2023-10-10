#include "piece.h"

void Piece::draw(int offset_x, int offset_y) {
    for (int x = 0; x < width(); x++) {
        for (int y = 0; y < height(); y++) {
			if (m_def.layout[m_orientation][x + y * 4]) {
				DrawRectangle(offset_x + (m_x * k_block_size) + (x * k_block_size),
							  offset_y + (m_y * k_block_size) + (y * k_block_size),
							  k_block_size, k_block_size, m_def.color);
			}
        }
    }
}

void Piece::next_piece(int piece_id) {
	m_piece_id = piece_id;
	m_def = s_pieces[piece_id];
	m_orientation = 0;
	m_x = 4;
	m_y = 0;
}