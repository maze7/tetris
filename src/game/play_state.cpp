#include "pch.h"
#include "play_state.h"

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
	int rect_width = 330;
	int rect_height = 660;

	int left = (GetScreenWidth() / 2) - (rect_width / 2);
	int right = (GetScreenWidth() / 2) + (rect_width / 2);
	int top = (GetScreenHeight()/2) - (rect_height/2);
	int bottom = (GetScreenHeight()/2) + (rect_height/2);

	// Grid Outline
	DrawRectangle(left, top, rect_width + (2*border_width), rect_height + (2*border_width), GRAY);
	DrawRectangle(left + border_width, top + border_width, rect_width, rect_height, BLACK);

	// Draw vertical grid lines
	for (int x = 1; x < 10; x++) {
		DrawLine((left + border_width) + (x * 32)+x, top + border_width, (left + border_width) + (x * 32)+x, bottom + 4, DARKGRAY);
	}

	// Draw horizontal grid lines
	for (int y = 1; y < 20; y++) {
		DrawLine(left + border_width, top + border_width + (y * 32) + y, right + 4, top + border_width + (y * 32) + y, DARKGRAY);
	}

	// Draw blocks
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 20; y++) {
			DrawRectangle(left + (x * 32) + x + border_width, top + (y * 32) + y + border_width, 32, 32, blocks[x][y].color);
		}
	}
}
