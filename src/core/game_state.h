#pragma once

class Game;

/**
 * GameState represents a single execution state the program can exist in; ie: MENU_STATE, PLAY_STATE, etc
 */
class GameState
{
public:
	GameState() = delete;
	GameState(Game* game) : m_game(game) {}

	virtual ~GameState() = default;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

protected:
	Game* m_game;
};

/**
 * Dummy state that performs no action ~ useful for testing
 */
class DummyState : public GameState
{
public:
	DummyState() = delete;
	DummyState(Game* game) : GameState(game) {}

	void update(float dt) override {}
	void draw() override {}
};