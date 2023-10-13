#pragma once

#include "pch.h"
#include "core/game_state.h"

/**
 * Displays the 10 ten scores of all time.
 */
class ScoreState : public GameState
{
public:
	ScoreState() = delete;
	ScoreState(Game* game);
	~ScoreState() override;

	/**
	 * Updates the internal state of the ScoreState. Called once per frame.
	 * @param dt the delta time between frames
	 */
	void update(float dt) override;

	/**
	 * Draws the current state of the ScoreState to the screen.
	 */
	void draw() override;


private:
	Font font;
};
