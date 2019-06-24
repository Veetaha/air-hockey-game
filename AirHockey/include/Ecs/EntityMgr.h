#pragma once

#include "Entity.h"

class EntityMgr {
public:
	void update(Uint32 deltaTime);
	void draw(SDL_Renderer& renderer);

	void addEntity(std::unique_ptr<Entity> entity);

private:
	void removeInActiveEntites();

	// Note: Entity should be a complete type when using std::unique_ptr without the custom deleter.
	std::vector<std::unique_ptr<Entity>> m_entities; 
};
