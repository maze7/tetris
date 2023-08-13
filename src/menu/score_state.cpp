#include "menu_state.h"
#include "score_state.h"
#include "core/game.h"

ScoreState::ScoreState(Game *game) : GameState(game) {}

ScoreState::~ScoreState() {}

void ScoreState::update(float dt) {}

void ScoreState::draw()
{
	int screen_width = GetScreenWidth();
	int screen_height = GetScreenHeight();

	DrawText("Top Scores", screen_width / 2 - MeasureText("Top Scores", 70) / 2, 50, 70, PURPLE);
	DrawText("Player 1: 9 475", screen_width / 2 - MeasureText("Player 1: 9 475", 22) / 2, 140, 22, PURPLE);
	DrawText("Player 2: 7 225", screen_width / 2 - MeasureText("Player 2: 7 225", 22) / 2, 180, 22, PURPLE);
	DrawText("Player 3: 7 180", screen_width / 2 - MeasureText("Player 3: 7 180", 22) / 2, 220, 22, PURPLE);
	DrawText("Player 4: 6 950", screen_width / 2 - MeasureText("Player 4: 6 950", 22) / 2, 260, 22, PURPLE);
	DrawText("Player 5: 6 920", screen_width / 2 - MeasureText("Player 5: 6 920", 22) / 2, 300, 22, PURPLE);
	DrawText("Player 6: 6 340", screen_width / 2 - MeasureText("Player 6: 6 340", 22) / 2, 340, 22, PURPLE);
	DrawText("Player 7: 5 200", screen_width / 2 - MeasureText("Player 7: 5 200", 22) / 2, 380, 22, PURPLE);
	DrawText("Player 8: 4 960", screen_width / 2 - MeasureText("Player 8: 4 960", 22) / 2, 420, 22, PURPLE);
	DrawText("Player 9: 4 590", screen_width / 2 - MeasureText("Player 9: 4 590", 22) / 2, 460, 22, PURPLE);
	DrawText("Player 10: 3 745", screen_width / 2 - MeasureText("Player 10: 3 745", 22) / 2, 500, 22, PURPLE);

	if (GuiButton({static_cast<float>(screen_width / 2 - 100), static_cast<float>(screen_height / 2 + 220), 200, 50}, "CLOSE"))
	{
		m_game->set_state(std::make_unique<MenuState>(m_game));
	}
}