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

	tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Shield.png");
	tex->setSmooth(true);
	m_player.m_shield.setTexture(tex);
	m_player.m_shield.setSize(sf::Vector2f(128.f, 128.f));
	m_player.m_shield.setOrigin(m_player.m_shield.getSize().x / 2, m_player.m_shield.getSize().y / 2);

    tex = ldResource.getTexture("assets/Graphics/Effects/electricity_chain.png");
    tex->setSmooth(true);
    m_player.m_rope.setTexture(tex);
    m_player.m_shield.setSize(sf::Vector2f(100.f, static_cast<float>(tex->getSize().y)));
    m_player.m_rope.setOrigin(tex->getSize().x / 2.f, static_cast<float>(tex->getSize().y));
	
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
	m_player.draw();
	for (auto &i:m_enemies)
	{
		i.draw();
	}
}

void ld::PlayState::addEnemy()
{

	m_enemies.emplace_back(*m_window);
	auto& ref = m_enemies.back();

	auto tex = ldResource.getTexture("assets/Graphics/Enemies/Alien_1_sheet.png");
	Animation anim;
	anim.load(*tex,3);
	anim.setChangeTime(0.5f);
	anim.start();
	ref.setAnimation(anim);
	ref.setTexture(tex);
	tex->setSmooth(true);
	ref.setSize(sf::Vector2f(256.f, 148.f));
	ref.setOrigin(ref.getSize().x / 2, ref.getSize().y / 2);
	ref.setPosition(1300.f,1300.f);
}