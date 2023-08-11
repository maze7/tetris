#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "menu_state.h"
#include <core/game.h>

class ConfigState : public GameState
{
public:
	ConfigState() = delete;
	ConfigState(Game* game);
	~ConfigState() override;

	void update(float dt) override;
	void draw() override;

private:

	float m_time = 0;

	int m_time_loc;
	int m_size_loc;

	float game_size = 10.0f;
	std::string difficulty = "medium";
	bool play_as_ai = false;
};