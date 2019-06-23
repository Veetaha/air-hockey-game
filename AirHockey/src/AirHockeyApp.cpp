#include "AirHockeyApp.h"
#include "SdlError.h"

AirHockeyApp::~AirHockeyApp() {
	SDL_Quit();
}

void AirHockeyApp::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		throw SdlError("Failed to initialize");
	}

	m_window.reset(SDL_CreateWindow(
		"Air Hockey (by Veetaha)",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		SDL_WINDOW_SHOWN
	));
	if (!m_window) {
		throw SdlError("Failed to create window.");
	}

	m_renderer = SDL_CreateRenderer(m_window.get(), -1, 0);

	if (!m_renderer) {
		throw SdlError("Failed to create renderer.");
	}

}

int AirHockeyApp::run() noexcept {
	try {
		while (isRunning) {
			waitAndHandleEvent();
			//update();
			render();
		}
	}
	catch (const std::exception& err) {
		std::cerr << err.what();
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown object was thrown whilst running the AirHockeyApp.";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void AirHockeyApp::waitAndHandleEvent() noexcept {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_EventType::SDL_QUIT: {
			isRunning = false;
			break;
		}
		default: break;
	}
}

void AirHockeyApp::render() {
	if (SDL_RenderClear(m_renderer)) {
		throw SdlError("Failed to clear the window.");
	}
	SDL_RenderPresent(m_renderer);
}

