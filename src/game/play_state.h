#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "piece.h"
#include "commands/command.h"
#include "input.h"
#include "grid.h"
#include "ai_controller.h"

class PlayState : public GameState
{
public:
	PlayState() = delete;
	PlayState(Game* game);
	~PlayState() override;

	void update(float dt) override;
	void draw() override;
	void game_over();

	[[nodiscard]] Game* game() { return m_game; }
	[[nodiscard]] int num_game_pieces() const;
	[[nodiscard]] int score() const { return m_score; }
	[[nodiscard]] int rows_cleared() const { return m_rows_cleared; }
	[[nodiscard]] int next_piece() const { return m_next_piece_id; }
	[[nodiscard]] double speed_multiplier() const;

	void set_score(int score) { m_score = score; }
	void set_rows_cleared(int lines) { m_rows_cleared = lines; }
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