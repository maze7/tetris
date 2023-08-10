#include "config_state.h"
#include <iostream>

ConfigState::ConfigState(Game *game) : GameState(game)
{
}

ConfigState::~ConfigState()
{
}

void ConfigState::update(float dt)
{
	m_time += dt;
}


bool width_text = true;
char game_width[256];
char game_height[256];

void ConfigState::draw()
{
	int screen_width = GetScreenWidth();
	int screen_height = GetScreenHeight();
	// Config Title
	const char *config_text = "Configuration";
	const int config_text_width = MeasureTextEx(GetFontDefault(), config_text, 70, 8).x;

	DrawText(config_text, (screen_width / 2 - config_text_width/2), 50, 70, PURPLE);

	Rectangle game_width_rec = { screen_width / 2 - 150, 170, 100, 30 };
	Rectangle game_height_rec = { screen_width / 2 +50, 170, 100, 30 };

	DrawText("Game Width", (screen_width / 2 - 220), 180, 10, PURPLE);
	DrawText("Game Height", (screen_width / 2-20), 180, 10, PURPLE);

	GuiTextBox(game_width_rec, game_width, 256, width_text);
	GuiTextBox(game_height_rec, game_height, 256, !width_text);

	const char *difficulty_text = "DIFFICULTY";
	const int diff_text_width = MeasureTextEx(GetFontDefault(), difficulty_text, 30, 3).x;

	// DrawRectangleLines(screen_width / 2 - 300, 225, 600, 150, RED);
	DrawText(difficulty_text, (screen_width / 2 - diff_text_width/2), 250, 30, PURPLE);

	if (GuiButton({static_cast<float>(screen_width / 2 -200), 300, 100, 50}, "EASY")){
		difficulty = "easy";
	}
	if (GuiButton({static_cast<float>(screen_width / 2 -50), 300, 100, 50}, "MEDIUM")){
		difficulty = "medium";
	}
	if (GuiButton({static_cast<float>(screen_width / 2 +100), 300, 100, 50}, "HARD")){
		difficulty = "hard";
	}
	
	Rectangle ai_button = { screen_width / 2 - 100, screen_height / 2 +100, 200, 50 };
	Rectangle ai_button_outline = { screen_width / 2 - 110, screen_height / 2 +80, 250, 60 };
	// if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 100), 200, 50}, "PLAY AS AI")) {
	// 		play_as_ai = !play_as_ai;
	// }
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), ai_button)) {
                play_as_ai = !play_as_ai;
            }
			if (CheckCollisionPointRec(GetMousePosition(), game_width_rec) || CheckCollisionPointRec(GetMousePosition(), game_height_rec)) {
                width_text = !width_text;
            }	
        }
	// Draw the switch
	DrawRectangleLines(screen_width / 2 - 101, screen_height / 2 + 99, 202, 52, WHITE);
	DrawRectangleRec(ai_button, play_as_ai ? GREEN : RED);
	DrawText("Play as AI", screen_width / 2 -50, screen_height / 2 + 115, 20, BLACK);
	

	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 200), 200, 50}, "MAIN MENU")) {
		m_game->set_state(std::make_unique<MenuState>(m_game));
	}
}