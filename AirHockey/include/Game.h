#pragma once

#include <iostream>

#include "TypeDefs.h"
#include "Ecs/EntityMgr.h"
#include "Dimensions2D.h"

class Game {
public:
	struct InitOpts {
		/** Defines maximum number of frames to be rendered per second. */
		Uint32 maxFps = 60;

		/** Defines height and width of the window to be created */
		Dimensions2D windowDimensions{ 1280, 720 };

		/** 
		 * Defines whether to open game in full-screen mode or not.
		 * If `true` .windowDimensions gets ignored.
		 */
		bool enableFullScreenMode{ false };
	};

	/**
	 * Constructs game manager with the `title` that will be used as the window name.
	 * 
	 * @param title Short string that will be displayed as the title of the game window.
	 */
	Game(std::string&& title): m_title(std::move(title)) {}

	/**
	 * Returns global game application rendering context.
	 */
	[[nodiscard]]
	SDL_Renderer& getRenderer() noexcept {
		return *m_renderer;
	}

	/**
	 * Returns global game application entity manager.
	 */
	[[nodiscard]]
	EntityMgr& getEntityManager() noexcept {
		return m_entityMgr;
	}

	~Game();

	/**
	 * Initializes the application. You must call this function only once and before .run().
	 * You should derive from this class and add your custom initialization logic after the call to .init().
	 * Most of the time you will be setting up the entity manager.
	 *
	 * @throws `SdlError` if initialization went wrong.
	 * 
	 * Application remains in an invalid state after an error was thrown. 
	 * No operations should be called on an invalid `AirHockeyApp`.
	 */
	virtual void init(const InitOpts& opts);

	/**
	 * Runs the game loop never throws, but if an error has occurred returns EXIT_FAILURE.
	 * Otherwise when the game loop has ended successfully returns EXIT_SUCCESS.
	 * 
     * Prerequisites: prior call to init() was made it didn't throw.
	 */
	int run() noexcept;

	/**
	 * Initializes and runs the application (shorthand for consequtive init() and run() calls).
	 * Handles all init() and runtime errors appropriately.
	 */
	int initAndRun(const InitOpts& opts) noexcept;

private:
	std::string m_title;

	EntityMgr m_entityMgr;

	SdlWindowUniquePtr m_window{ nullptr };

	SdlRendererUniquePtr m_renderer{ nullptr };

	bool isRunning{ true };

	Uint32 m_maxFps{ 60 };

	/**
	 * Waits (polls) for the next event in SDL event loop and handles it appropriately.
	 * 
	 * @throws Everithing that SDL_PollEvent() throws since it was not declared `noexcept`.
	 */
	void waitAndHandleEvent();
	
	void runImpl();

	void update(Uint32 deltaTime);

	/**
	 * Re-renders the current scene single time.

	 * @throws `SdlError` if an error has occurred while rendering.
	 */
	void render();
};

