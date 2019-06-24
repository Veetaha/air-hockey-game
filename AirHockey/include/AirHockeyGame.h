#pragma once

#include "Game.h"

class AirHockeyGame : public Game {
public:
	using Super = Game;

	AirHockeyGame(): Game("AirHockeyGame (by Veetaha)") {}

	void init(const InitOpts& opts) override;

};