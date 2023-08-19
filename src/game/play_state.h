#pragma once

#include "pch.h"
#include "core/game_state.h"

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
	bool m_show_dialog = false;
	Block blocks[10][20];

	void draw_stats();
	void draw_next_block();
	void draw_help();
	void draw_grid();
};