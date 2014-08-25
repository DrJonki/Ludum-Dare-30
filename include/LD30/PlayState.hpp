#pragma once

#include <LD30/GameState.hpp>
#include <LD30/Entity/Player.hpp>
#include <LD30/Entity/Enemy.hpp>
#include <LD30/Entity/Explosion.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>
#include <memory>
#include <vector>

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

		void addExplosion(sf::Vector2f pos);

	private:

		Player m_player;
		std::vector<Enemy> m_enemies;
		std::vector<Explosion> m_explosions;
		float m_spawnTime, m_Time, m_minTime, m_enemySpeed, m_enemySpeedMin;
		int m_difficulty;
		bool easterEgg;
		sf::Vector2f getRandSpawnPos();
		void collisionCheck();
        sf::Music m_music;
        sf::RectangleShape m_background;
        sf::RectangleShape m_lifeIcon;
        sf::RectangleShape m_killIcon;
        unsigned int m_kills;
        sf::Text m_scoreText;
        sf::Text m_killsText;

        unsigned int m_score;
        sf::Clock m_scoreClock;

        enum MenuState
        {
            Pause,
            GameOver,
            Count
        };

        std::array<std::unique_ptr<BaseMenu>, Count> m_menus;
        MenuState m_menuState;
	};
}