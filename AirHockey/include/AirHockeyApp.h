#pragma once

#include <iostream>

#include "TypeDefs.h"

class AirHockeyApp final {
public:

	~AirHockeyApp();

	/**
	 * Initializes the application. You must call this function only once and before run().
	 *
	 * @throws `SdlError` if initialization went wrong.
	 * 
	 * Application remains in an invalid state after an error was thrown. 
	 * No operations should be called on an invalid `AirHockeyApp`.
	 */
	void init();

	/**
	 * Runs the game loop never throws, but if an error has occurred returns EXIT_FAILURE.
	 * Otherwise when the game loop has ended successfully returns EXIT_SUCCESS.
	 * 
     * Prerequisites: prior call to init() was made it didn't throw.
	 */
	int run() noexcept;

private:
	SdlWindowUniquePtr m_window{ nullptr, SDL_DestroyWindow };

	SDL_Renderer* m_renderer{ nullptr };

	bool isRunning{ true };

	/**
	 * Waits (polls) for the next event in SDL event loop and handles it appropriately.
	 */
	void waitAndHandleEvent() noexcept;
	
	/**
	 * Re-renders the current scene single time.

	 * @throws `SdlError` if an error has occurred while rendering.
	 */
	void render();

};

