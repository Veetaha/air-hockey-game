#include "TextureMgr.h"
#include "Utils.h"
#include "Errors.h"

std::shared_ptr<SDL_Texture> TextureMgr::createTextureFromFile(
	SDL_Renderer& renderer,
	const char * const filePath
) {

	const SdlSurfaceUniquePtr surface(Utils::notNullOrThrow<SdlImgError>(
		IMG_Load(filePath)
	));

	return {
		Utils::notNullOrThrow<SdlError>(SDL_CreateTextureFromSurface(&renderer, surface.get())),
		SDL_DestroyTexture
	};
}

Dimensions2D TextureMgr::getTextureDimensions(SDL_Texture& texture) {
	Dimensions2D dimensions;
	if (SDL_QueryTexture(&texture, nullptr, nullptr, &dimensions.width, &dimensions.height)) {
		throw SdlError("Failed to query texture dimensions");
	}
	return dimensions;
}
