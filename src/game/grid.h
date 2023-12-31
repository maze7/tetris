#pragma once

#include "piece.h"
#include <vector>

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
		PieceCollision = PieceDown | PieceHorizontal,

		// If a piece or the floor is blocking the piece from moving down
		Blocked 	= PieceDown | Floor,
	};
}

class AIController;

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
	 * Returns whether the top row of the grid is clear
	 * @return true or false
	 */
	[[nodiscard]] bool top_row_clear() const;

	/**
	 * Counts the number of holes in the grid for a specific column
	 * @return integer representing the number of holes
	 */
	 [[nodiscard]] int count_holes(int x) const;

	 /**
	  * Returns the value of the cell at the specified coordinates
	  * @param x
	  * @param y
	  * @return
	  */
	 [[nodiscard]] int cell_value(int x, int y) const;

	/**
	 * Draws the entire grid at the specified pixel coordinates
	 * @param x position of top-left corner of grid
	 * @param y position of top-left corner of grid
	 */
	void draw(int x, int y, Texture& block, Piece piece) const;

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
	void place_piece(Piece& piece);

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
	std::vector<int> m_cells;

	friend class AIController;
};