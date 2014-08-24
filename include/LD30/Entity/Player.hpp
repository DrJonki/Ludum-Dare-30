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

		void movePlayer(const float delta);
		void moveShield(const float delta);

		sf::RectangleShape m_shield;
	private:
		sf::Vector2f m_direction;

		sf::Vector2f m_shieldDir;
	};
}