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
		void keyInput(const float delta);

		void moveShield(const float delta);
        void handleRope();

		sf::RectangleShape m_shield;
        sf::RectangleShape m_rope;
	private:
		sf::Vector2f m_direction;

		sf::Vector2f m_shieldDir;
	};
}