#pragma once

#include "Component.h"

class Entity {
public:
	
	[[nodiscard]] 
	constexpr bool isActive() const noexcept {
		return m_isActive;
	}

	void update(Uint32 deltaTime);
	void draw(SDL_Renderer& renderer);
	void destroy() noexcept {
		m_isActive = false;
	}

	template <typename TComponent, typename... TArgs >
	TComponent& setComponent(TArgs&&... args) {
		auto& newComponent(static_cast<TComponent&>(
			*m_components.emplace(
				Component::getTypeId<TComponent>(),
				std::make_unique<TComponent>(this, std::forward<TArgs>(args)...)
			).first->second
		));
		newComponent.init();
		return newComponent;
	}

	template <typename TComponent>
	[[nodiscard]] 
	TComponent& getComponent() {
		const auto targetIt{ m_components.find(Component::getTypeId<TComponent>()) };
		SDL_assert(targetIt != m_components.end());
		return static_cast<TComponent&>(*targetIt->second);
	}

private:
	std::unordered_map<Component::IdType, std::unique_ptr<Component>> m_components;
	bool m_isActive{ true };

};

