#include "Ecs/Entity.h"

void Entity::update(Uint32 deltaTime) {
	for (auto& kv: m_components) {
		kv.second->update(deltaTime);
	}
}

void Entity::draw(SDL_Renderer& renderer) {
	for (const auto& kv : m_components) {
		kv.second->draw(renderer);
	}
}
