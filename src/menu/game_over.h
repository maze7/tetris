#pragma once

#include "core/game_state.h"

class GameOverState : public GameState
{
public:
	GameOverState() = delete;
	GameOverState(Game* game, int score);
	~GameOverState() override;

	void update(float dt) override;
	void draw() override;

private:
	Texture m_game_over;
	int 	m_score;
	bool	m_should_save_score = false;
};