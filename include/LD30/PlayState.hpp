#pragma once

#include <LD30/GameState.hpp>
#include <array>
#include <memory>
#include <vector>
#include <LD30/Entity/Player.hpp>
#include <LD30/Entity/Enemy.hpp>

namespace ld
{
	class PlayState : public GameState
	{
	public:
		PlayState(sf::RenderWindow& window);

		~PlayState() final override;

		bool init() final override;

		void update(const float delta) final override;

		void draw() final override;

		void addEnemy();

	private:

		Player m_player;
		std::vector<Enemy> m_enemies;
	};
}