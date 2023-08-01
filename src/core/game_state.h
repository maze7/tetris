#pragma once

/**
 * GameState represents a single execution state the program can exist in; ie: MENU_STATE, PLAY_STATE, etc
 */
class GameState
{
public:
	virtual ~GameState() = default;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;
};

/**
 * Dummy state that performs no action ~ useful for testing
 */
class DummyState : public GameState
{
public:
	void update(float dt) override {}
	void draw() override {}
};