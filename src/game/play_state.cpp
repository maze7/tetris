#include <menu/menu_state.h>
#include "pch.h"
#include "play_state.h"
#include "core/game.h"
#include "commands/move_command.h"
#include "commands/rotate_command.h"
#include "core/config.h"
#include <sstream>

PlayState::PlayState(Game* game) : GameState(game), m_piece(4, -1) {

}

PlayState::~PlayState() {

}

void PlayState::update(float dt) {
    // move piece downwards until bottom of board
    if ((m_piece.y() + m_piece.height()) < 20) {
        m_tick += dt;

        if (m_tick >= 0.75) {
            m_tick = 0;

			// move piece down once per tick
			MoveCommand(0, 1).execute(m_piece, *this);
        }

		// get input command from user
		auto command = InputSystem::handle_input();
		if (command)
			command->execute(m_piece, *this);
    }

    // exit dialog
	if (IsKeyPressed(KEY_ESCAPE))
		m_show_dialog = !m_show_dialog;
}

void PlayState::draw() {
	draw_grid();
    draw_stats();
    draw_next_block();

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

void PlayState::draw_stats() {
    int border_width = 4;
    int rect_width = 300;
    int rect_height = 320;
    int main_rect_height = 640;

    int left = (GetScreenWidth()/2) - (rect_width + (rect_width * 0.5)) - 20;
    int right = (GetScreenWidth() / 2);
    int top = (GetScreenHeight()/2) - (main_rect_height/2);
    int bottom = (GetScreenHeight()/2) + (rect_height/2);

    // draw bg & frame
    DrawRectangle(left, top, rect_width, rect_height, GRAY);
    DrawRectangle(left + border_width,
                  top + border_width,
                  rect_width - border_width * 2,
                  (rect_height * 0.15), BLACK);
    DrawRectangle(left + border_width,
                  top + border_width + (rect_height * 0.15) + border_width,
                  rect_width - border_width * 2,
                  (rect_height * 0.8), BLACK);

	std::string player_mode_text = "Player Mode: ";
	std::string game_type_text = "Game Type: ";
	std::string difficulty_text = "Difficulty: ";

    // messy magic numbers for now, no point tidying up until we decide on a proper UI
    DrawText("Stats:", left + 16, top + 16, 20, WHITE);
    DrawText("Group: 8", left + 16, top + 64, 18, WHITE);
    DrawText("Score: 0", left + 16, top + 92, 18, WHITE);
    DrawText("Lines Eliminated: 0", left + 16, top + 120, 18, WHITE);
    DrawText("Current Level: 0", left + 16, top + 148, 18, WHITE);
    DrawText((player_mode_text + (m_game->config().game_mode == GameMode::Player ? "Player" : "AI")).c_str(), left + 16, top + 176, 18, WHITE);
    DrawText((game_type_text + (m_game->config().game_type == GameType::Normal ? "Normal" : "Extended")).c_str(), left + 16, top + 204, 18, WHITE);
}

void PlayState::draw_next_block() {
    int border_width = 4;
    int rect_width = 64 + 16;
    int rect_height = 64 + 16;
    int main_rect_width = 320;
    int main_rect_height = 640;

    int left = (GetScreenWidth()/2) + (main_rect_width/2) + 16;
    int top = (GetScreenHeight()/2) - (main_rect_height/2);

    DrawRectangle(left, top, rect_width + (border_width*2), rect_height + (border_width*2), GRAY);
    DrawRectangle(left + border_width, top + border_width, rect_width, rect_height, BLACK);

    int grid[2][2] = { 1, 1, 1, 1 };
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            if (grid[x][y]) {
                DrawRectangle(left + (x * 32) + border_width + 8, top + (y * 32) + border_width + 8, 32, 32, YELLOW);
            }
        }
    }
}

void PlayState::draw_help() {

}

void PlayState::draw_grid() {
	const Config& cfg = m_game->config();

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
	for (int x = 1; x < cfg.board_width; x++) {
		DrawLine((left + border_width) + (x * 32), top + border_width, (left + border_width) + (x * 32), bottom + 4, DARKGRAY);
	}

	// Draw horizontal grid lines
	for (int y = 1; y < cfg.board_height; y++) {
		DrawLine(left + border_width, top + border_width + (y * 32), right + 4, top + border_width + (y * 32), DARKGRAY);
	}

    m_piece.draw(left + border_width, top + border_width);
}
