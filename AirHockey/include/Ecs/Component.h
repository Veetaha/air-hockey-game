#pragma once

class Entity;

class Component {
public:

	explicit Component(Entity* owningEntity): 
		m_owningEntity(owningEntity) 
	{}

	using IdType = Uint16;

	/**
	 * Returns an id number for the given component type.
	 * All components have their own unique ids based on their type.
	 *
	 * @param TComponent The type of the component to get id for.
	 */
	template <typename TComponent>
	[[nodiscard]]
	static constexpr IdType getTypeId() noexcept {
		// generates new index upon each instantiation
		const static IdType index{ s_nextComponentId++ }; 
		return index;
	}

	virtual ~Component() {}

	virtual void init() {}
	virtual void update(Uint32 deltaTime) {}
	virtual void draw(SDL_Renderer& renderer) {}

	[[nodiscard]]
	Entity& getOwningEntity() noexcept;

private: 
	Entity* const m_owningEntity;

	static inline IdType s_nextComponentId{ 0 };
};