#pragma once

#include "pch.h"
#include "game_state.h"
#include "config.h"

class Game
{
public:
	Game();
	~Game();

	void update(float dt);
	void draw();

	void set_state(std::unique_ptr<GameState> new_state);

	[[nodiscard]] bool should_exit() const;
	[[nodiscard]] Config& config();

    void request_exit() {
        exit_requested = true;
    }

private:
	std::unique_ptr<GameState> m_current_state = nullptr;
	std::unique_ptr<GameState> m_next_state = nullptr;

	Config m_config;

	int m_width = 0;
	int m_height = 0;

	bool exit_requested = false;
};