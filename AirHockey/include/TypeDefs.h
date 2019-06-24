#pragma once

#include <memory>
#include <iostream>

#include "Finalizer.h"

template <typename TInstance, void (*finalizer)(TInstance *)>
using UniquePtrWithFinalizer = std::unique_ptr<TInstance, Finalizer<TInstance, finalizer>>;

using SdlSurfaceUniquePtr  = UniquePtrWithFinalizer<SDL_Surface,  SDL_FreeSurface>;
using SdlWindowUniquePtr   = UniquePtrWithFinalizer<SDL_Window,   SDL_DestroyWindow>;
using SdlRendererUniquePtr = UniquePtrWithFinalizer<SDL_Renderer, SDL_DestroyRenderer>;
using SdlTextureUniquePtr  = UniquePtrWithFinalizer<SDL_Texture,  SDL_DestroyTexture>;

using Vector2D = Eigen::Matrix<float, 2, 1>;