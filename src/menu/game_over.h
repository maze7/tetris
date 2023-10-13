#pragma once

#include "core/game_state.h"

/**
 * GameState responsible for displaying the "Game Over" screen and score.
 */
class GameOverState : public GameState
{
public:
	GameOverState() = delete;

	/**
	 * Caches a pointer to the Game class that owns this GameOverState. Determines whether the score is in the top 10.
	 * @param game
	 * @param score
	 */
	GameOverState(Game* game, int score);

	/**
	 * Cleans up any memory allocated by the GameOverState
	 */
	~GameOverState() override;

	/**
	 * The main update method of the GameOverState. Called once per frame by the Game class. Used to update the internal state of the
	 * GameOverState.
	 * @param dt the delta time between frames
	 */
	void update(float dt) override;

	/**
	 * Draws the current state of the GameOverState to the screen.
	 */
	void draw() override;

private:
	Texture m_game_over;
	int 	m_score;
	bool	m_should_save_score = false;
};