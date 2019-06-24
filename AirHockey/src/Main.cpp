#include "AirHockeyGame.h"

int main(int, char*[]) {
	AirHockeyGame game;
	AirHockeyGame::InitOpts initOpts;
	return game.initAndRun(initOpts);
}