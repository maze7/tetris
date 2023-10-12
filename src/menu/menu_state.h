#pragma once

#include "pch.h"
#include "core/game_state.h"

class MenuState : public GameState
{
public:
	MenuState() = delete;
	MenuState(Game* game);
	~MenuState() override;

	void update(float dt) override;
	void draw() override;

private:
	Texture m_logo;

	float m_time = 0;
};