#pragma once

#include "Ecs/Component.h"
#include "Dimensions2D.h"

class SpriteComponent : public Component {
public:
	SpriteComponent(
		class Entity*  owningEntity,
		std::shared_ptr<SDL_Texture>&& texture,
		Dimensions2D&& destDimenions,
		SDL_Rect&&     srcRect
	);

	SpriteComponent(
		class Entity*  owningEntity,
		std::shared_ptr<SDL_Texture>&& texture,
		Dimensions2D&& destDimensions
	);

	void draw(SDL_Renderer& renderer) override;

private:
	std::shared_ptr<SDL_Texture> m_texture;
	SDL_Rect m_srcRect;
	Dimensions2D m_destDimensions;

	class MovementComponent& m_entityMovement;
};