#pragma once

#include "pch.h"
#include "core/game_state.h"

class PlayState : public GameState
{
public:
	PlayState() = delete;
	PlayState(Game* game);
	~PlayState() override;

	void update(float dt) override;
	void draw() override;

private:

};