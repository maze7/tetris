#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "piece.h"
#include "commands/command.h"
#include "input.h"
#include "grid.h"
#include "ai_controller.h"

/**
 * Implements the main "Play" screen of the game. Manages everything related to the game loop.
 */
class PlayState : public GameState
{
public:
	PlayState() = delete;

	/**
	 * Constructs a new play state owned by the provided Game pointer
	 * @param game pointer to the Game which owns this state
	 */
	explicit PlayState(Game* game);

	/**
	 * Destructor which destroys any created assets
	 */
	~PlayState() override;

	/**
	 * The main 'tick' of the game method. Called once per frame and handles all logic updates of the game.
	 * @param dt the delta time between the current frame and the previous frame
	 */
	void update(float dt) override;

	/**
	 * Draws the current state of the game to the screen
	 */
	void draw() override;

	/**
	 * Used to trigger the end of the PlayState. Moves the Game to the GameOver state.
	 */
	void game_over();

	/**
	 * Utillity accessor to access the Game pointer. (Mostly used to access the Config from within the PlayState)
	 * @return pointer to the Game that owns this state
	 */
	[[nodiscard]] Game* game() { return m_game; }

	/**
	 * Accessor for the number of pieces in the current game mode (Normal / Extended)
	 * @return integer value representing the number of available pieces
	 */
	[[nodiscard]] int num_game_pieces() const;

	/**
	 * Accessor for the current score of the game.
	 * @return current score as integer
	 */
	[[nodiscard]] int score() const { return m_score; }

	/**
	 * Accessor for the number of rows cleared for the current session
	 * @return number of rows cleared
	 */
	[[nodiscard]] int rows_cleared() const { return m_rows_cleared; }

	/**
	 * Accessor for the ID of the next piece which will be played
	 * @return the ID of the upcoming piece
	 */
	[[nodiscard]] int next_piece() const { return m_next_piece_id; }

	/**
	 * Calculates the speed multiplier as the user clears lines. Decreases the downtime between 'ticks' which move the block downward.
	 * @return
	 */
	[[nodiscard]] double speed_multiplier() const;

	/**
	 * Sets the current game score
	 * @param score the new score
	 */
	void set_score(int score) { m_score = score; }

	/**
	 * Sets the number of rows cleared for the current session
	 * @param lines the number of lines that have been cleared
	 */
	void set_rows_cleared(int lines) { m_rows_cleared = lines; }

	/**
	 * Sets the next piece which will be played for the current session
	 * @param piece_id the ID of the next piece
	 */
	void set_next_piece(int piece_id) { m_next_piece_id = piece_id; }

	static constexpr int k_points_lookup[] = {0, 100, 300, 600, 1000};
	static constexpr double k_downtimes[] = { 0.75, 0.5, 0.25 };

private:
    float m_tick = 0;
	float m_ai_tick = 0;
	bool m_show_dialog = false;
	bool m_paused = false;
	int m_score = 0;
	int m_rows_cleared = 0;
	float m_music_pitch = 1;
	bool m_game_over = false;

	AIController m_ai;
	Piece m_ai_prediction;

	Grid m_grid;
	Piece m_piece;
	int m_next_piece_id;

	Texture m_block;

	void draw_stats() const;
	void draw_next_block() const;

	friend class AIController;
};