#include "AirHockeyApp.h"

int main(int, char*[]) {
	AirHockeyApp GameApp;

	try {
		GameApp.init();
	} catch (const std::exception& err) {
		std::cerr << err.what();
		return EXIT_FAILURE;
	}

	return GameApp.run();
}