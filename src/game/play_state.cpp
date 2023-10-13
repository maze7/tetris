#include <menu/menu_state.h>
#include "pch.h"
#include "play_state.h"
#include "core/game.h"
#include "commands/move_command.h"
#include "commands/rotate_command.h"
#include "core/config.h"
#include <sstream>
#include <menu/game_over.h>
#include <algorithm>

PlayState::PlayState(Game* game) :
	GameState(game),
	m_grid(game->config().board_width, game->config().board_height),
	m_ai(*this, m_grid)
{
	m_block = LoadTexture("res/block.png");
	m_piece.next_piece((m_grid.width() / 2) - (m_piece.width()/2), 0, rand() % num_game_pieces());
	set_next_piece(rand() % num_game_pieces());
}

PlayState::~PlayState() {
	UnloadTexture(m_block);
	SetMusicPitch(m_game->music(), 1);
}

void PlayState::update(float dt) {
	if (m_game_over) {
		m_game->set_state(std::make_unique<GameOverState>(m_game, score()));
		return;
	}


	// update music speed as difficulty increases
	const float pitch = 1 + (0.0075 * std::max(m_rows_cleared, 0));
	if (pitch != m_music_pitch) {
		m_music_pitch = pitch;
		SetMusicPitch(m_game->music(), m_music_pitch);
	}

    // move piece downwards until bottom of board
	if (!m_paused) {
		if ((m_piece.y() + m_piece.height()) < m_grid.height() + 1) {
			m_tick += dt;
			m_ai_tick += dt;

			// calculate time between game ticks according to difficulty level
			double downtime = speed_multiplier() * 1;

			if (m_tick >= downtime) {
				m_tick = 0;

				// move piece down once per tick
				MoveCommand(0, 1).execute(m_piece, m_grid, *this);
			}

			// if we are in a player-controlled game, get the player's input
			if (m_game->config().game_mode == GameMode::Player) {
				// get input command from user
				auto command = InputSystem::handle_input();

				if (command)
					command->execute(m_piece, m_grid, *this);

			} else { // otherwise execute AI command
				if (m_ai_tick >= 0.1) {
					auto command = m_ai.generate_command(m_piece);

					if (command)
						command->execute(m_piece, m_grid, *this);

					m_ai_tick = 0;
					std::cout << "ai tick" << std::endl;
				}
			}
		} else {
			m_piece.next_piece((m_grid.width() / 2) - (m_piece.width()/2), 0, next_piece());
			set_next_piece(rand() % num_game_pieces());
		}
	}

	// Pause game
	if (IsKeyPressed(KEY_P))
		m_paused = !m_paused;

    // exit dialog
	if (IsKeyPressed(KEY_ESCAPE)) {
		m_show_dialog = !m_show_dialog;
		m_paused = m_show_dialog;
	}
}

void PlayState::draw() {
	if (m_game_over)
		return;

	int grid_x = GetScreenWidth()/2 - (Grid::k_cell_size * m_grid.width())/2 - Grid::k_cell_size;
	int grid_y = GetScreenHeight()/2 - (Grid::k_cell_size * m_grid.height())/2 - Grid::k_cell_size/2;

	m_grid.draw(grid_x, grid_y, m_block, m_piece);
	m_piece.draw(grid_x, grid_y, m_block, 255);

	//draw_grid();
    draw_stats();
    draw_next_block();

	if (m_paused)
		DrawText("PAUSED", 25, GetScreenHeight() - 50, 30, WHITE);

    // draw quit dialog
    if (m_show_dialog) {
        // box background & border
        DrawRectangle(GetScreenWidth()/2 - 205, GetScreenHeight()/2 - 105, 410, 210, DARKGRAY);
        DrawRectangle(GetScreenWidth()/2 - 200, GetScreenHeight()/2 - 100, 400, 200, LIGHTGRAY);

        // dialog text
        DrawText("Do you want to exit?", GetScreenWidth()/2 - 110, GetScreenHeight()/2 - 25, 20, BLACK);

        // exit button
        if (GuiButton({ (float)GetScreenWidth()/2 - 190, (float)GetScreenHeight()/2 + 40, 180, 50}, "Yes"))
            game_over();

		// resume button
        if (GuiButton({ (float)GetScreenWidth()/2 + 10, (float)GetScreenHeight()/2 + 40, 180, 50}, "No")) {
            m_show_dialog = false;
			m_paused = false;
        }
    }
}

void PlayState::draw_stats() const {
	int left = (GetScreenWidth()/2) + ((m_grid.width() * Grid::k_cell_size)/2) + 16;
	int top = GetScreenHeight()/2 - (Grid::k_cell_size * m_grid.height())/2 - Grid::k_cell_size + 256;
	int bottom = (GetScreenHeight()/2) + (Grid::k_cell_size * (m_grid.height()/2)) - Grid::k_cell_size;

	constexpr int font_size = 24;

	static const std::string difficulties[] = { "EASY", "MEDIUM", "HARD" };
	static const std::string game_types[] = { "NORMAL", "EXTENDED" };
	static const std::string player_modes[] = { "PLAYER", "AI" };

	const std::string stats[] = {
		std::string("SCORE  ") + std::to_string(score()),
		std::string("LINES  ") + std::to_string(rows_cleared()),
		std::string("LEVEL  ") + difficulties[(int)m_game->config().difficulty],
		std::string("MODE   ") + player_modes[(int)m_game->config().game_mode],
		std::string("TYPE   ") + game_types[(int)m_game->config().game_type],
	};

	for (int i = 4; i >= 0; i--) {
		DrawText(stats[i].c_str(), left, bottom - ((4 - i) * 48), font_size, WHITE);
	}
}

void PlayState::draw_next_block() const {
	int left = (GetScreenWidth()/2) + ((m_grid.width() * Grid::k_cell_size)/2) + 32;
	int top = GetScreenHeight()/2 - (Grid::k_cell_size * m_grid.height())/2 - Grid::k_cell_size + 32;

	DrawText("NEXT", left, top, 28, WHITE);

	PieceDefinition def = s_pieces[m_next_piece_id];

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (def.layout[0][x + y * 4]) {
				DrawTexture(m_block,
							left + (x * Piece::k_block_size) + (x*2),
							top + (y * Piece::k_block_size) + (y*2) + 48,
							def.color);
			}
		}
	}
}

void PlayState::game_over() {
	m_game_over = true;
}

int PlayState::num_game_pieces() const {
	return m_game->config().game_type == GameType::Normal ? 7 : 9;
}

double PlayState::speed_multiplier() const {
	const double decrease_factor = 0.15;

	int levels_increase = m_rows_cleared / 10;
	double new_downtime = k_downtimes[(int)m_game->config().difficulty] - levels_increase * decrease_factor;

	return std::max(new_downtime, 0.10);
}
