#pragma once

#include "game/piece.h"

class PlayState;
class Command
{
public:
	virtual ~Command() = default;

	virtual void execute(Piece& piece, PlayState& ps) = 0;
};