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


	return true;
}

void ld::PlayState::update(const float delta)
{
	m_player.update(delta);
}

void ld::PlayState::draw()
{
	m_window->draw(m_player);
}

