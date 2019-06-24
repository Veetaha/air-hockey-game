#pragma once
#include "TypeDefs.h"
#include "Dimensions2D.h"

class TextureMgr {
public:
	/**
	 * Returns a texture loaded from the given `filePath`.
	 * 
	 * @throws `SdlError` or `SdlImgError` if loading any loading error occurred.
	 */
	[[nodiscard]]
	static std::shared_ptr<SDL_Texture> createTextureFromFile(
		SDL_Renderer& renderer, 
		const char * const filePath
	);

	/**
	 * Retrieves source texture width and height.
	 * @throws `SdlError` if failed.
	 */
	static Dimensions2D getTextureDimensions(SDL_Texture& texture);

};

