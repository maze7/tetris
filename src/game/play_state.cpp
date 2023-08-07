#include "pch.h"
#include "play_state.h"

PlayState::PlayState(Game* game) : GameState(game) {

}

PlayState::~PlayState() {

}

void PlayState::update(float dt) {

}

void PlayState::draw() {
	DrawText("tetris", 200, 200, 20, WHITE);
}
