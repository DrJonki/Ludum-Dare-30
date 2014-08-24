#include <LD30/Entity/Player.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

const float speed = 250.f;
const float maxspeed = 100.f;
const float drag = 0.8f;
const float friction = 80.f;
const float border = 80.f;

const float ropeLenghtSquared = powf(150,2);
const float shieldDrag = 0.2f;
const float shieldFriction = 20.f;
const float shieldMassMultiplier = 0.0001f;
const float shieldSpeedMultiplier = 0.05f;


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
	movePlayer(delta);
	moveShield(delta);
}

void ld::Player::draw()
{
	m_window->draw(*this);
	m_window->draw(m_shield);
}

void ld::Player::movePlayer(const float delta)
{
	const sf::Vector2f pos = (*this).getPosition();
	float x;
	float y;

	if (pos.x < border)
	{
		x = 1;
	}
	else if (1920 - border < pos.x)
	{
		x = -1;
	}
	else
	{
		x = static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) -
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	}


	if (pos.y < border)
	{
		y = 1;
	}
	else if (1080 - border < pos.y)
	{
		y = -1;
	}
	else
	{
		y = static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) -
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
	}

	m_direction += delta * sf::Vector2f(x * speed, y * speed);

	const float mag = std::sqrt(m_direction.x*m_direction.x + m_direction.y*m_direction.y);
	if (mag > maxspeed)
	{
		sf::Vector2f normalize = m_direction / mag;
		m_direction = normalize*maxspeed;
	}
	this->move(m_direction*delta);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		m_direction -= (m_direction / mag) * friction * delta;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		m_direction *= 1 - drag * delta;
	}
	else
	{
		m_direction -= (m_direction / mag) * friction * delta;
		m_direction *= 1 - drag * delta;
	}
}

void ld::Player::moveShield(const float delta)
{
	sf::Vector2f dif = (*this).getPosition() - m_shield.getPosition();

	float magSquared = dif.x*dif.x + dif.y*dif.y;
	if (magSquared > ropeLenghtSquared)
	{
		m_shieldDir += (dif / magSquared) * sqrt(magSquared - ropeLenghtSquared) / shieldMassMultiplier * delta;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		m_shieldDir -= (m_shieldDir / sqrt(magSquared)) * shieldFriction * delta;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		m_shieldDir *= 1 - shieldDrag * delta;
	}
	else
	{
		m_shieldDir -= (m_shieldDir / sqrt(magSquared)) * shieldFriction * delta;
		m_shieldDir *= 1 - shieldDrag * delta;
	}

	m_shield.move(m_shieldDir * shieldSpeedMultiplier * delta);
}