#include "piece.h"

void Piece::draw(int offset_x, int offset_y) {
    for (int x = 0; x < width(); x++) {
        for (int y = 0; y < height(); y++) {
            if (orientations[m_orientation][x + y * height()]) {
                DrawRectangle(offset_x + (m_x * k_block_size) + (x * k_block_size),
                              offset_y + (m_y * k_block_size) + (y * k_block_size),
                              k_block_size, k_block_size, k_piece_color);
            }
        }
    }
}
