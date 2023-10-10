#pragma once

#include "piece.h"

/**
 * Bitmask used to determine what collision results a collision check has returned
 */
namespace Collision {
	enum Result {
		NoCollision = 0,

		// Collision checks for grid boundaries
		Wall 		= 1 << 0,
		Floor 		= 1 << 1,
		Boundary 	= Wall | Floor,

		// Collision checks with other pieces
		PieceLeft	= 1 << 2,
		PieceRight  = 1 << 3,
		PieceDown	= 1 << 4,

		// piece horizontal & any piece collisions
		PieceHorizontal = PieceLeft | PieceRight,
		PieceCollision = PieceDown | PieceHorizontal
	};
}

/**
 * Class responsible for managing the current state of the tetris grid
 */
class Grid
{
public:
	/**
	 * Constructs an instance of the Grid
	 * @param width width of the grid (in cells)
	 * @param height height of the grid (in cells)
	 */
	Grid(int width, int height);

	/**
	 * Grid destructor
	 */
	~Grid();

	/**
	 * Returns the current width of the grid (in cells)
	 * @return
	 */
	[[nodiscard]] int width() const { return m_width; }

	/**
	 * Returns the current height of the grid (in cells)
	 * @return
	 */
	[[nodiscard]] int height() const { return m_height; }

	/**
	 * Draws the entire grid at the specified pixel coordinates
	 * @param x position of top-left corner of grid
	 * @param y position of top-left corner of grid
	 */
	void draw(int x, int y) const;

	/**
	 * Determines whether a piece with a given pattern will collide at a specific position
	 * @param x piece x cell position
	 * @param y piece y cell position
	 * @param piece piece which should be checked against the grid
	 * @return
	 */
	int collision_check(int x, int y, Piece& piece) const;

	/**
	 *
	 * @param x
	 * @param y
	 * @param piece
	 */
	void place_piece(int x, int y, Piece& piece) const;

	/**
	 * Clears any completed rows from the grid
	 * @return number of lines cleared
	 */
	int clear_rows();

	static constexpr int k_cell_size = 32;
	static constexpr int k_border_width = 4;
private:
	// grid dimensions
	int m_width, m_height;

	// grid cell values
	int* m_cells = nullptr;
};