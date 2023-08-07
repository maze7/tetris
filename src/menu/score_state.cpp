#include "menu_state.h"
#include "score_state.h"
#include "core/game.h"

ScoreState::ScoreState(Game* game) : GameState(game) {}

ScoreState::~ScoreState() {}

void ScoreState::update(float dt) {}

void ScoreState::draw() {
	int screen_width = GetScreenWidth();
	int screen_height = GetScreenHeight();

    DrawText("Top Scores", screen_width/2 - 100, 25, 42, WHITE);
	DrawText("Player 1: 9 475", screen_width/2 - 100, 100, 22, WHITE);
	DrawText("Player 2: 7 225", screen_width/2 - 100, 140, 22, WHITE);
	DrawText("Player 3: 7 180", screen_width/2 - 100, 180, 22, WHITE);
	DrawText("Player 4: 6 950", screen_width/2 - 100, 220, 22, WHITE);
	DrawText("Player 5: 6 920", screen_width/2 - 100, 260, 22, WHITE);
	DrawText("Player 6: 6 340", screen_width/2 - 100, 300, 22, WHITE);
	DrawText("Player 7: 5 200", screen_width/2 - 100, 340, 22, WHITE);
	DrawText("Player 8: 4 960", screen_width/2 - 100, 380, 22, WHITE);
	DrawText("Player 9: 4 590", screen_width/2 - 100, 420, 22, WHITE);
	DrawText("Player 10: 3 745", screen_width/2 - 100, 460, 22, WHITE);

	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 220), 200, 50}, "CLOSE")) {
		m_game->set_state(std::make_unique<MenuState>(m_game));
	}
}