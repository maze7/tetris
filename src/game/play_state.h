#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "piece.h"
#include "commands/command.h"
#include "input.h"

struct Block
{
	Color color = ColorAlpha(BLACK, 0);
};

class PlayState : public GameState
{
public:
	PlayState() = delete;
	PlayState(Game* game);
	~PlayState() override;

	void update(float dt) override;
	void draw() override;

	Game* game() { return m_game; }

private:
    float m_tick = 0;
	bool m_show_dialog = false;
	bool m_paused = false;

	Piece m_piece;
	int m_next_piece_id;

	void draw_stats();
	void draw_next_block();
	void draw_help();
	void draw_grid();
};