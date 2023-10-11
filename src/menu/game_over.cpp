#include "game_over.h"
#include "core/game.h"
#include "menu_state.h"

GameOverState::GameOverState(Game* game) : GameState(game) {

}

GameOverState::~GameOverState() {

}

void GameOverState::update(float dt) {

}

void GameOverState::draw() {
	if (GuiButton({ static_cast<float>(GetScreenWidth()/2 - 110), static_cast<float>((GetScreenHeight()/4) * 3), 100, 50}, "MAIN MENU"))
		m_game->set_state(std::make_unique<MenuState>(m_game));
}
