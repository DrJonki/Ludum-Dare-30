#include <LD30/Entity/Player.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

ld::Player::Player(sf::RenderWindow &window)
:Entity(window)
{
	m_direction = sf::Vector2f(0,0);
}

ld::Player::~Player()
{

}

void ld::Player::update(const float delta)
{
	keyInput(delta);
	const float mag = std::sqrt(m_direction.x*m_direction.x + m_direction.y*m_direction.y);
	const float maxspeed = 100;
	if (mag > maxspeed)
	{
		sf::Vector2f normalize = m_direction / mag;
		m_direction = normalize*maxspeed;
	}
	this->move(m_direction*delta);
	m_direction *= 0.9999f-delta/10;
}

void ld::Player::keyInput(const float delta)
{
	sf::Vector2f temp;
	const float speed = 50.f*delta;

	temp += sf::Vector2f(
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) * speed, 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) * speed);

	m_direction += temp;
}
