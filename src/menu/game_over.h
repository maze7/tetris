#pragma once

#include "core/game_state.h"

class GameOverState : public GameState
{
public:
	GameOverState() = delete;
	GameOverState(Game* game);
	~GameOverState() override;

	void update(float dt) override;
	void draw() override;
};