#pragma once

#include <LD30/Entity/Entity.hpp>

namespace ld
{
	class Player;

	class Enemy : public Entity
	{
	public:
		Enemy(sf::RenderWindow &window);
		~Enemy();
		void update(const float dt) final override;
		void setPlayer(Player &player);
	private:
		Player* m_player;
		void move(const float delta);
	};
}