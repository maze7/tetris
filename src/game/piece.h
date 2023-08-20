#pragma once

class Piece
{
public:
    Piece(int x, int y) : m_x(x), m_y(y), m_orientation(0) {}

    void rotate();
    void move(int x, int y);
    void draw(int offset_x, int offset_y);

    int x() const { return m_x; }
    int y() const { return m_y; }
    int width() const { return 3; }
    int height() const { return 3; }

private:
    // temporary L piece for prototype
    int orientations[4][9] = {
        {
            0, 0, 0,
            1, 1, 0,
            0, 1, 1,
        },
        {
            0, 1, 0,
            1, 1, 0,
            1, 0, 0,
        },
        {
                0, 0, 0,
                1, 1, 0,
                0, 1, 1,
        },
        {
                0, 1, 0,
                1, 1, 0,
                1, 0, 0,
        },
    };

    int m_x;
    int m_y;
    int m_orientation;

    // temporary constants
    static constexpr int k_block_size = 32;
    static constexpr Color k_piece_color = RED;
};