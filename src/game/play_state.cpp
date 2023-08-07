#include "pch.h"
#include "play_state.h"

PlayState::PlayState(Game* game) : GameState(game) {

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

	// Grid Outline
	DrawRectangle((GetScreenWidth() / 2) - (rect_width / 2), (GetScreenHeight()/2) - (rect_height/2), rect_width + (2*border_width), rect_height + (2*border_width), WHITE);
	DrawRectangle((GetScreenWidth() / 2) - (rect_width / 2) + border_width, (GetScreenHeight()/2) - (rect_height/2) + border_width, rect_width, rect_height, BLACK);

	// Draw vertical grid lines
	for (int x = 1; x < 10; x++) {
		DrawLine(((GetScreenWidth() / 2) - (rect_width / 2) + border_width) + (x * 32)+x, (GetScreenHeight()/2) - (rect_height/2) + border_width, ((GetScreenWidth() / 2) - (rect_width / 2) + border_width) + (x * 32)+x, (GetScreenHeight()/2) + (rect_height/2) + 4, DARKGRAY);
	}

	// Draw horizontal grid lines
	for (int y = 1; y < 20; y++) {
		DrawLine((GetScreenWidth() / 2) - (rect_width / 2) + border_width, (GetScreenHeight()/2) - (rect_height/2) + border_width + (y * 32)+y, (GetScreenWidth() / 2) + (rect_width / 2), (GetScreenHeight()/2) - (rect_height/2) + border_width + (y * 32)+y, DARKGRAY);
	}
}
