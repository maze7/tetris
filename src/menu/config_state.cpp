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

	//Game width and height boxes
	Rectangle game_width_rec = { screen_width / 2 - 150, screen_height/3.5, 100, 30 };
	Rectangle game_height_rec = { screen_width / 2 + 50, screen_height/3.5, 100, 30 };

	DrawText("Game Width", (screen_width / 2 - 220), screen_height/3.5 + 10, 10, PURPLE);
	DrawText("Game Height", (screen_width / 2 - 20), screen_height/3.5 + 10, 10, PURPLE);

	GuiTextBox(game_width_rec, game_width, 256, width_text);
	GuiTextBox(game_height_rec, game_height, 256, !width_text);

	//Difficulty title and boxes
	const char *difficulty_text = "DIFFICULTY";
	const int diff_text_width = MeasureTextEx(GetFontDefault(), difficulty_text, 30, 3).x;

	DrawText(difficulty_text, (screen_width / 2 - diff_text_width/2), screen_height/2.5, 30, PURPLE);

	if (GuiButton({static_cast<float>(screen_width / 2 - 200), static_cast<float>(screen_height/2.5 + 50), 100, 50}, "EASY")){
		difficulty = "easy";
	}
	if (GuiButton({static_cast<float>(screen_width / 2 -50), static_cast<float>(screen_height/2.5 + 50), 100, 50}, "MEDIUM")){
		difficulty = "medium";
	}
	if (GuiButton({static_cast<float>(screen_width / 2 +100), static_cast<float>(screen_height/2.5 + 50), 100, 50}, "HARD")){
		difficulty = "hard";
	}
	
	//AI button
	Rectangle ai_button = { screen_width / 2 - 211, screen_height / 2 +100, 200, 50 };
	Rectangle ai_button_outline = { screen_width / 2 - 220, screen_height / 2 +80, 250, 60 };
	
	//extended game button
	Rectangle extended_game_button = { screen_width / 2 + 10, screen_height / 2 +100, 200, 50 };
	Rectangle extended_game_outline = { screen_width / 2, screen_height / 2 +80, 250, 60 };

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), ai_button)) {
                play_as_ai_toggle = !play_as_ai_toggle;
            }
			if (CheckCollisionPointRec(GetMousePosition(), extended_game_button)) {
                extended_game_toggle = !extended_game_toggle;
            }
			if (CheckCollisionPointRec(GetMousePosition(), game_width_rec) || CheckCollisionPointRec(GetMousePosition(), game_height_rec)) {
                width_text = !width_text;
            }	
        }

	DrawRectangleLines(screen_width / 2 - 212, screen_height / 2 + 99, 202, 52, WHITE);
	DrawRectangleRec(ai_button, play_as_ai_toggle ? GREEN : RED);
	DrawText("Play as AI", screen_width / 2 - 160, screen_height / 2 + 115, 20, BLACK);

	DrawRectangleLines(screen_width / 2 + 9, screen_height / 2 + 99, 202, 52, WHITE);
	DrawRectangleRec(extended_game_button, extended_game_toggle ? GREEN : RED);
	DrawText("Extended Game", screen_width / 2 + 35, screen_height / 2 + 115, 20, BLACK);
	
	//Main menu button
	if (GuiButton({ static_cast<float>(screen_width/2 - 100), static_cast<float>(screen_height/2 + 200), 200, 50}, "MAIN MENU")) {
		m_game->set_state(std::make_unique<MenuState>(m_game));
	}
}