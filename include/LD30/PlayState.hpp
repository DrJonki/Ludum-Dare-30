#pragma once

#include <LD30/GameState.hpp>
#include <array>
#include <memory>
#include <vector>
#include <LD30/Entity/Player.hpp>
#include <LD30/Entity/Enemy.hpp>

namespace ld
{
    class BaseMenu;

	class PlayState : public GameState
	{
	public:
		PlayState(sf::RenderWindow& window);

		~PlayState() final override;

		bool init() final override;

		void update(const float delta) final override;

		void draw() final override;

		void addEnemy();

		void countTimeForEnemies();

		void setDifficulty(int dif);

	private:

		Player m_player;
		std::vector<Enemy> m_enemies;
		float m_spawnTime, m_Time, m_minTime;
		int difficulty, startLives;
		bool easterEgg;
		sf::Vector2f getRandSpawnPos();
		bool ifCollide(sf::RectangleShape A, sf::RectangleShape B);
		void collisionCheck();


        enum MenuState
        {
            Pause,
            GameOver,
            Count
        };

        std::array<std::unique_ptr<BaseMenu>, Count> m_menus;
	};
}