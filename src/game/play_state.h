#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "piece.h"
#include "commands.h"
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

private:
    float m_tick = 0;
	bool m_show_dialog = false;
	Piece m_piece;

	void draw_stats();
	void draw_next_block();
	void draw_help();
	void draw_grid();
};