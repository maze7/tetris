#pragma once

#include <game/grid.h>

class PlayState;
class Command
{
public:
	virtual ~Command() = default;

	virtual void execute(Piece& piece, Grid& grid, PlayState& state) = 0;
};