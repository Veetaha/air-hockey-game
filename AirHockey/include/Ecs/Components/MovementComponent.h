#pragma once

#include "TypeDefs.h"
#include "Ecs/Component.h"

class MovementComponent : public Component {
public:

	explicit MovementComponent(
		class Entity * owningEntity, 
		Vector2D&& initialLocation = { 0, 0 },
		Vector2D&& initialVelocity = { 0, 0 }
	) : 
		Component(owningEntity),
		m_location(std::move(initialLocation)), 
		m_velocity(std::move(initialVelocity)) 
	{}

	void update(Uint32 deltaTime) override {
		m_location += m_velocity * static_cast<float>(deltaTime) / 1000.0f;
	}

	[[nodiscard]] constexpr Vector2D& getVelocity() & noexcept { return m_velocity; }
	[[nodiscard]] constexpr Vector2D& getLocation() & noexcept { return m_location; }

	[[nodiscard]] constexpr const Vector2D& getVelocity() const& noexcept { return m_velocity; }
	[[nodiscard]] constexpr const Vector2D& getLocation() const& noexcept { return m_location; }

	void setVelocity(Vector2D&& newVelocity) noexcept {
		m_velocity = std::move(newVelocity);
	}

	void setLocation(Vector2D&& newLocation) noexcept {
		m_location = std::move(newLocation);
	}

private:
	Vector2D m_location{ 0, 0 };
	Vector2D m_velocity{ 0, 0 }; // pixels per second
};