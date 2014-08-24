#include <LD30/PlayState.hpp>
#include <LD30/ResourceManager.hpp>
#include <LD30/Engine.hpp>
#include <SFML/Graphics/Texture.hpp>

ld::PlayState::PlayState(sf::RenderWindow& window)
	: GameState(window),
	m_player(window)
{

}

ld::PlayState::~PlayState()
{

}

bool ld::PlayState::init()
{
	//Player
	auto tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Player_Base.png");
	tex->setSmooth(true);
	m_player.setTexture(tex);
	m_player.setSize(sf::Vector2f(128.f,128.f));
	m_player.setOrigin(m_player.getSize().x / 2, m_player.getSize().y / 2);

	//Enemy
	addEnemy();

	return true;
}

void ld::PlayState::update(const float delta)
{
	m_player.update(delta);

	for (int i = 0; i < (int)m_enemies.size(); ++i)
	{
		m_enemies[i].setPlayer(m_player);
		m_enemies[i].update(delta);
	}
}

void ld::PlayState::draw()
{
	m_window->draw(m_player);
	for (int i = 0; i < (int)m_enemies.size(); ++i)
	{
		m_window->draw(m_enemies[i]);
	}
}

void ld::PlayState::addEnemy()
{

	m_enemies.emplace_back(*m_window);
	auto& ref = m_enemies.back();

	auto tex = ldResource.getTexture("assets/Graphics/Enemies/Alien_1_1.png");
	tex->setSmooth(true);
	ref.setSize(sf::Vector2f(128.f, 128.f));
	ref.setOrigin(ref.getSize().x / 2, ref.getSize().y / 2);
	ref.setPosition(1300.f,1300.f);
}