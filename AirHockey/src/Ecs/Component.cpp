#include "Ecs/Component.h"
#include "Ecs/Entity.h"

Entity& Component::getOwningEntity() noexcept {
	SDL_assert(m_owningEntity);
	return *m_owningEntity;
}
