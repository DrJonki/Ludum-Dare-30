#pragma once

#include <LD30/Entity/Entity.hpp>

namespace ld
{
	class Player : public Entity
	{
	public:
		Player(sf::RenderWindow &window);
		~Player();
		void update(const float delta) final override;
		void draw() final override;

		sf::RectangleShape m_shield;

	private:
		void movePlayer(const float delta);

		void shieldMovement(const float delta);
		void shieldRubberband(const float delta);
		void shieldSlow(const float delta);

		sf::Vector2f m_direction;

		sf::Vector2f m_shieldDir;
	};
}