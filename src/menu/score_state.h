#pragma once

#include "pch.h"
#include "core/game_state.h"

class ScoreState : public GameState
{
public:
	ScoreState() = delete;
	ScoreState(Game* game);
	~ScoreState() override;
	

	void update(float dt) override;
	void draw() override;

private:
	Font font;
};
