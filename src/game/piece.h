#pragma once

#include "piece_definitions.h"

// forward declare commands that can act upon a piece
class MoveCommand;
class RotateCommand;

/**
 * Piece represents a given Tetromino on the grid. It is used for the currently active piece, as well as for AI Calculations.
 */
class Piece
{
public:
	/**
	 * Default constructor
	 */
	Piece() = default;

	/**
	 * Constructs a piece of type piece_id at the provided location.
	 * @param x location on the x coordinate
	 * @param y location on the y coordinate
	 * @param piece_id the id of the piece
	 */
	Piece(int x, int y, int piece_id);

	/**
	 * Accessor for the current x position of the piece
	 * @return x position as cell index
	 */
	[[nodiscard]] int x() const { return m_x; }

	/**
	 * Accessor for the current y position of the piece
	 * @return y position as cell index
	 */
	[[nodiscard]] int y() const { return m_y; }

	/**
	 * Accessor for the current piece width
	 * @return width as number of blocks
	 */
	[[nodiscard]] int width() const { return s_pieces[m_piece_id].width[m_orientation]; }

	/**
	 * Accessor for the current piece height
	 * @return height as number of blocks
	 */
	[[nodiscard]] int height() const { return s_pieces[m_piece_id].height[m_orientation]; }

	/**
	 * Accessor for current piece orientation (rotation)
	 * @return integer representing the current orientation index (0 - 3)
	 */
	[[nodiscard]] int orientation() const { return m_orientation; }

	/**
	 * Accessor for the current piece color
	 * @return The current color of the piece
	 */
	[[nodiscard]] Color color() const { return s_pieces[m_piece_id].color; }

	/**
	 * Accessor for the id of the current piece type. (L, Z, S, etc)
	 * @return integer ID representing piece type
	 */
	[[nodiscard]] int current_piece_id() const { return m_piece_id; }

	/**
	 * Accessor for the PieceDefinition for the current piece
	 * @return the current piece's PieceDefinition struct (used to determine the archetype of the piece)
	 */
	[[nodiscard]] const PieceDefinition& definition() const { return m_def; }

	/**
	 * Accessor to the current Piece's layout (the locations of the pieces blocks)
	 * @return 4x4 integer array outlining the locations of each block in the piece
	 */
	[[nodiscard]] const int* layout() const { return m_def.layout[m_orientation]; }

	/**
	 * Mutator to move the piece to a specific x position. Should not be used to move pieces on the board, should only be used for simulations.
	 * @param x the new x position of the piece
	 */
	void set_x(int x) { m_x = x; }

	/**
	 * Mutator to move the piece to a specific y position. Should not be used to move pieces on the board, should only be used for simulations.
	 * @param y the new y position of the piece
	 */
	void set_y(int y) { m_y = y; }

	/**
	 * Mutator to set the rotation of the piece. Should not be used to move pieces on the board, should only be used for simulations.
	 * @param x the new x position
	 */
	void set_rotation(int x) { m_orientation = x; }

	/**
	 * Resets the PieceDefinition of the piece to the next provided ID, moves the piece to the provided coordinates and resets the orientation.
	 * @param x start position of the piece
	 * @param y start position of the piece
	 * @param piece_id the new ID for the PieceDefinition of the next piece
	 */
	void next_piece(int x, int y, int piece_id);

	/**
	 * Draws a piece at a specific location on the screen.
	 * @param offset_x the pixel offset on the x coordinate (this is used to align the piece with the grid)
	 * @param offset_y the pixel offset on the y coordinate (this is used to align the piece with the grid)
	 * @param block reference to the block texture that should be used for drawing
	 * @param alpha the alpha valu the piece should be drawn with (used for ghost / placement preview)
	 */
	void draw(int offset_x, int offset_y, Texture& block, int alpha);

	/**
	 * Constant storing the size of a block in pixels
	 */
	static constexpr int k_block_size = 32;

private:
	int m_x 			= 4;
	int m_y 			= -1;
	int m_orientation 	= 0;
	int m_piece_id 		= 0;

	PieceDefinition m_def;

	friend class MoveCommand;
	friend class DropCommand;
	friend class RotateCommand;
};
