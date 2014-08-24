#pragma once

#include <LD30/Entity/Entity.hpp>
#include <LD30/Entity/Animation.hpp>

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
		void setAnimation(Animation &animation);
	private:
		Player* m_player;
		Animation m_animation;
		void move(const float delta);
	};
}