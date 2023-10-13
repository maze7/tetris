#pragma once

#include "pch.h"
#include "core/game_state.h"

/**
 * Displays the Main Menu for the game.
 */
class MenuState : public GameState
{
public:
	MenuState() = delete;
	MenuState(Game* game);
	~MenuState() override;

	/**
	 * Updates the internal state of the MenuState. Called once per frame.
	 * @param dt the delta time between frames
	 */
	void update(float dt) override;

	/**
	 * Draws the current state of the MenuState to the screen.
	 */
	void draw() override;

private:
	Texture m_logo;

	float m_time = 0;
};