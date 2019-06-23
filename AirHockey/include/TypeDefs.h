#pragma once

#include <SDL.h>

#include <memory>

using SdlWindowUniquePtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;