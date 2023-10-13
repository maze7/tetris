#include "piece.h"

void Piece::draw(int offset_x, int offset_y, Texture& block, int alpha) {
    for (int x = 0; x < width(); x++) {
        for (int y = 0; y < height(); y++) {
			if (m_def.layout[m_orientation][x + y * 4]) {
				DrawTexture(block,
							offset_x + (x * Piece::k_block_size) + (x*2) + (m_x*k_block_size) + (m_x*2),
							offset_y + (y * Piece::k_block_size) + (y*2) + (m_y*k_block_size) + (m_y*2),
							Color(m_def.color.r, m_def.color.g, m_def.color.b, alpha));
			}
        }
    }
}

void Piece::next_piece(int x, int y, int piece_id) {
	m_piece_id = piece_id;
	m_def = s_pieces[piece_id];
	m_orientation = 0;
	m_x = x;
	m_y = y;
}

Piece::Piece(int x, int y, int piece_id) {
	m_piece_id = piece_id;
	m_def = s_pieces[piece_id];
	m_orientation = 0;
	m_x = x;
	m_y = y;
}
