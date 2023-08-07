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
	Shader m_crt_shader;

	float m_time = 0;

	// TODO (Callan): We'll need a shader wrapper class which handles these. It's messy leaving them as class members
	int m_time_loc;
	int m_size_loc;
};