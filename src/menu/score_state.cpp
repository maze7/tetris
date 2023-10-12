#include <core/scores.h>
#include "menu_state.h"
#include "score_state.h"
#include "core/game.h"

ScoreState::ScoreState(Game *game) : GameState(game) {}

ScoreState::~ScoreState() {}

void ScoreState::update(float dt) {}

void ScoreState::draw()
{
	int score_width = GetScreenWidth()/3 * 2;
	int score_height = GetScreenHeight()/3 * 2;
	Scores::draw({
		(float) GetScreenWidth()/2 - score_width/2,
		(float) 32,
		(float) score_width,
		(float) score_height
	});

	if (GuiButton({static_cast<float>(GetScreenWidth() / 2 - 100), static_cast<float>(GetScreenHeight() - 96), 200, 50}, "CLOSE"))
	{
		m_game->set_state(std::make_unique<MenuState>(m_game));
	}
}