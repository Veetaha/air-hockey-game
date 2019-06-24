#include "Ecs/Components/SpriteComponent.h"
#include "Ecs/Components/MovementComponent.h"
#include "Ecs/Entity.h"
#include "Errors.h"
#include "TextureMgr.h"

SpriteComponent::SpriteComponent(
	Entity*		   owningEntity,
	std::shared_ptr<SDL_Texture>&& texture,
	Dimensions2D&& destDimensions,
	SDL_Rect&&	   srcRect
):
	Component(owningEntity),
	m_texture(std::move(texture)),
	m_destDimensions(std::move(destDimensions)),
	m_srcRect(std::move(srcRect)),
	m_entityMovement(getOwningEntity().getComponent<MovementComponent>())
{
	
}

SpriteComponent::SpriteComponent(
	Entity *	   owningEntity, 
	std::shared_ptr<SDL_Texture> && texture, 
	Dimensions2D&& destDimensions
): 
	SpriteComponent(
		owningEntity, 
		std::move(texture), 
		std::move(destDimensions), 
		TextureMgr::getTextureDimensions(*texture).toSdlRectAt(Vector2D(0, 0))
	)
{}

void SpriteComponent::draw(SDL_Renderer & renderer) {
	const auto destRect{ m_destDimensions.toSdlRectAt(m_entityMovement.getLocation()) };

	if (SDL_RenderCopy(&renderer, m_texture.get(), &m_srcRect, &destRect)) {
		throw SdlError("Failed to render SpriteComponent");
	}
}
