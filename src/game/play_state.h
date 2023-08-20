#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "piece.h"

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

private:
    float m_tick = 0;
	bool m_show_dialog = false;
	Piece m_piece;

	void draw_stats();
	void draw_next_block();
	void draw_help();
	void draw_grid();

    static constexpr int k_board_width = 10;
    static constexpr int k_board_height = 20;
};