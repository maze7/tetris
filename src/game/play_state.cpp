#include <menu/menu_state.h>
#include "pch.h"
#include "play_state.h"
#include "core/game.h"

PlayState::PlayState(Game* game) : GameState(game) {
	blocks[0][0].color = RED;
	blocks[1][0].color = RED;
	blocks[2][0].color = RED;

	blocks[5][5].color = YELLOW;
	blocks[6][5].color = YELLOW;
	blocks[5][6].color = YELLOW;
}

PlayState::~PlayState() {

}

void PlayState::update(float dt) {
	if (IsKeyPressed(KEY_ESCAPE))
		m_show_dialog = !m_show_dialog;
}

void PlayState::draw() {
	draw_grid();
}

void PlayState::draw_stats() {

}

void PlayState::draw_next_block() {

}

void PlayState::draw_help() {

}

void PlayState::draw_grid() {
	int border_width = 4;
	int rect_width = 320;
	int rect_height = 640;

	int left = (GetScreenWidth() / 2) - (rect_width / 2);
	int right = (GetScreenWidth() / 2) + (rect_width / 2);
	int top = (GetScreenHeight()/2) - (rect_height/2);
	int bottom = (GetScreenHeight()/2) + (rect_height/2);

	// Grid Outline
	DrawRectangle(left, top, rect_width + (2*border_width), rect_height + (2*border_width), GRAY);
	DrawRectangle(left + border_width, top + border_width, rect_width, rect_height, BLACK);

	// Draw vertical grid lines
	for (int x = 1; x < 10; x++) {
		DrawLine((left + border_width) + (x * 32), top + border_width, (left + border_width) + (x * 32), bottom + 4, DARKGRAY);
	}

	// Draw horizontal grid lines
	for (int y = 1; y < 20; y++) {
		DrawLine(left + border_width, top + border_width + (y * 32), right + 4, top + border_width + (y * 32), DARKGRAY);
	}

	// Draw blocks
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 20; y++) {
			DrawRectangle(left + (x * 32) + border_width, top + (y * 32) + border_width, 32, 32, blocks[x][y].color);
		}
	}

	// draw quit dialog
	if (m_show_dialog) {
		// box background & border
		DrawRectangle(GetScreenWidth()/2 - 205, GetScreenHeight()/2 - 105, 410, 210, DARKGRAY);
		DrawRectangle(GetScreenWidth()/2 - 200, GetScreenHeight()/2 - 100, 400, 200, LIGHTGRAY);

		// dialog text
		DrawText("Do you want to exit?", GetScreenWidth()/2 - 110, GetScreenHeight()/2 - 25, 20, BLACK);

		// exit button
		if (GuiButton({ (float)GetScreenWidth()/2 - 190, (float)GetScreenHeight()/2 + 40, 180, 50}, "Yes")) {
			m_game->set_state(std::make_unique<MenuState>(m_game));
		}

		if (GuiButton({ (float)GetScreenWidth()/2 + 10, (float)GetScreenHeight()/2 + 40, 180, 50}, "No")) {
			m_show_dialog = false;
		}
	}
}
