#include "Ecs/EntityMgr.h"
#include "Ecs/Entity.h"

void EntityMgr::update(Uint32 deltaTime) {
	for (auto& entity : m_entities) {
		entity->update(deltaTime);
	}
}

void EntityMgr::draw(SDL_Renderer& renderer) {
	for (const auto& entity : m_entities) {
		entity->draw(renderer);
	}
}

void EntityMgr::addEntity(std::unique_ptr<Entity> entity) {
	m_entities.emplace_back(std::move(entity));
}

void EntityMgr::removeInActiveEntites() {
	const auto removedBegin(std::remove_if(begin(m_entities), end(m_entities), [](const std::unique_ptr<Entity> & entity) {
		return !entity->isActive();
	}));
	m_entities.erase(removedBegin, end(m_entities));
}
