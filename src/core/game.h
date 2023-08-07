#pragma once

#include "pch.h"
#include "game_state.h"

class Game
{
public:
	Game();
	~Game();

	void update(float dt);
	void draw();

	void set_state(std::unique_ptr<GameState> new_state);

	[[nodiscard]] bool should_exit() const;

private:
	std::unique_ptr<GameState> m_current_state = nullptr;
	std::unique_ptr<GameState> m_next_state = nullptr;

	int m_width = 0;
	int m_height = 0;
};