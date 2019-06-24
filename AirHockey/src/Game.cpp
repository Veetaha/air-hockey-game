#include "Game.h"
#include "Errors.h"
#include "Utils.h"

Game::~Game() {
	SDL_Quit();
	IMG_Quit();
}

void Game::init(const InitOpts& opts) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		throw SdlError("Failed to initialize SDL module");
	}

	if (const int imgInitFlags = IMG_INIT_PNG; IMG_Init(imgInitFlags) != imgInitFlags) {
		throw SdlImgError("Failed to initialize SDL image module");
	}
	{
		using Flags = SDL_WindowFlags;
		m_window.reset(Utils::notNullOrThrow<SdlError>(SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			opts.windowDimensions.width,
			opts.windowDimensions.height,
			Flags::SDL_WINDOW_SHOWN | (opts.enableFullScreenMode ? Flags::SDL_WINDOW_FULLSCREEN : 0)
		)));
	}
	{
		using Flags = SDL_RendererFlags;

		m_renderer.reset(Utils::notNullOrThrow<SdlError>(SDL_CreateRenderer(
			m_window.get(), -1, Flags::SDL_RENDERER_ACCELERATED | Flags::SDL_RENDERER_PRESENTVSYNC
		)));
	}

	m_maxFps = opts.maxFps;
}

int Game::run() noexcept {
	try {
		runImpl();
	}
	catch (const std::exception& err) {
		std::cerr << err.what();
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown object was thrown whilst running the Game.";
		return EXIT_FAILURE;
	} 
	return EXIT_SUCCESS;
}

void Game::runImpl() {
	// TODO: move inside the loop if max FPS may be changed during the game.
	const Uint32 maxFrameDuration{ 1000 / m_maxFps };
	Uint32 lastUpdateCallTime{ SDL_GetTicks() };
	while (isRunning) {
		const Uint32 timeBeforeFrame{ SDL_GetTicks() }; // in milliseconds
		waitAndHandleEvent();
		update(SDL_GetTicks() - lastUpdateCallTime);
		lastUpdateCallTime = SDL_GetTicks();
		render();
		const Uint32 frameDuration{ SDL_GetTicks() - timeBeforeFrame };
		if (frameDuration < maxFrameDuration) {
			SDL_Delay(maxFrameDuration - frameDuration);
		}
	}
}

int Game::initAndRun(const InitOpts& opts) noexcept {
	try {
		init(opts);
	}
	catch (const std::exception & err) {
		std::cerr << err.what();
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown object was thrown during the app initialization.";
		return EXIT_FAILURE;
	}
	return run();
}

void Game::waitAndHandleEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EventType::SDL_QUIT: {
				isRunning = false;
				break;
			}
			default: break;
		}
	}
}

void Game::render() {
	if (SDL_RenderClear(m_renderer.get())) {
		throw SdlError("Failed to clear the window.");
	}
	m_entityMgr.draw(*m_renderer);
	SDL_RenderPresent(m_renderer.get());
}

void Game::update(Uint32 deltaTime) {
	m_entityMgr.update(deltaTime);
}