#pragma once

#include "pch.h"
#include "core/game_state.h"
#include "menu_state.h"
#include <core/game.h>

/**
 * Main Screen used to configure the settings of the game
 */
class ConfigState : public GameState
{
public:
	ConfigState() = delete;

	/**
	 * ConfigState constructor. Caches a pointer to the Game which owns this state
	 * @param game
	 */
	ConfigState(Game* game);

	/**
	 * Clears any used resources for the ConfigState
	 */
	~ConfigState() override;

	/**
	 * Called once per game frame, used to update internal logic of the ConfigState.
	 * @param dt the delta time between frames
	 */
	void update(float dt) override;

	/**
	 * Draws the current state of the GameState to the screen
	 */
	void draw() override;

private:
	float m_time = 0;
	int m_time_loc;
	int m_size_loc;
	float game_size = 10.0f;
	std::string difficulty = "medium";
	bool play_as_ai_toggle = false;
	bool extended_game_toggle = false;
};