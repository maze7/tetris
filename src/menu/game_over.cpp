#include <core/scores.h>
#include <game/play_state.h>
#include "game_over.h"
#include "core/game.h"
#include "menu_state.h"

bool input_selected = false;
char name[256];

GameOverState::GameOverState(Game* game, int score) : GameState(game), m_score(score) {
	m_game_over = LoadTexture("res/game_over.png");
	m_should_save_score = Scores::is_top_10(m_score) && m_score > 0 && m_game->config().game_mode != GameMode::AI;

	if (m_game->config().game_mode == GameMode::AI)
		Scores::add("AI", score);
}

GameOverState::~GameOverState() {
	UnloadTexture(m_game_over);
}

void GameOverState::update(float dt) {
}

void GameOverState::draw() {
	DrawTexture(m_game_over, GetScreenWidth()/2 - 322, 16, WHITE);

	int score_width = GetScreenWidth()/3 * 2;
	int score_height = GetScreenHeight()/3 * 2;
	Scores::draw({
			 (float) GetScreenWidth()/2 - score_width/2,
			 (float) 112,
			 (float) score_width,
			 (float) score_height
	 });

	if (GuiButton({ static_cast<float>(GetScreenWidth()/2 - 210), static_cast<float>((GetScreenHeight() - 64)), 200, 50}, "MAIN MENU"))
		m_game->set_state(std::make_unique<MenuState>(m_game));

	if (GuiButton({ static_cast<float>(GetScreenWidth()/2 + 10), static_cast<float>((GetScreenHeight() - 64)), 200, 50}, "PLAY AGAIN"))
		m_game->set_state(std::make_unique<PlayState>(m_game));

	// draw save score diagram if needed
	if (m_should_save_score) {
		int dialog_width = 400;
		int dialog_height = 200;
		int dialog_x = GetScreenWidth()/2 - dialog_width/2;
		int dialog_y = GetScreenHeight()/2 - dialog_height/2;

		// box background & border
		DrawRectangle(dialog_x - 2, dialog_y - 2, dialog_width + 4, dialog_height + 4, DARKGRAY);
		DrawRectangle(dialog_x, dialog_y, dialog_width, dialog_height, LIGHTGRAY);

		// dialog text
		int text_width = MeasureText("High score! Enter name:", 20);
		DrawText("High score! Enter name:", dialog_x + dialog_width/2 - text_width/2, dialog_y + (0.15 * dialog_height), 20, BLACK);

		// draw text input
		const Rectangle input_rectangle = { (float)dialog_x + dialog_width/2 - text_width/2, (float)(dialog_y + (0.4 * dialog_height)), (float)text_width, 42 };
		GuiTextBox(input_rectangle, name, 20, input_selected);

		// focus text input
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			if (CheckCollisionPointRec(GetMousePosition(), input_rectangle)) {
				input_selected = true;
			} else {
				input_selected = false;
			}
		}

		// save button
		if (GuiButton({ (float) dialog_x + (dialog_width/2) - 90, (float)dialog_y + dialog_height - 55, 180, 50}, "SAVE")) {
			Scores::add(std::string(name).empty() ? "player" : name, m_score);
			m_should_save_score = false;
		}
	}
}
