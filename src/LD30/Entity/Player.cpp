#include <LD30/Entity/Player.hpp>
#include <SFML/Window.hpp>

ld::Player::Player(sf::RenderWindow &window)
:Entity(window)
{

}

ld::Player::~Player()
{

}

void ld::Player::update(const float delta)
{
	keyInput(delta);
}

void ld::Player::keyInput(const float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->move(sf::Vector2f(-10.f*delta, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->move(sf::Vector2f(10.f*delta, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->move(sf::Vector2f(0.f, 10.f*delta));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->move(sf::Vector2f(0.f, -10.f*delta));
	}
}