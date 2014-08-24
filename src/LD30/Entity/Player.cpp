#include <LD30/Entity/Player.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

const float speed = 250.f;
const float maxspeed = 100.f;
const float friction = 0.0001f;

const float ropeLenghtSquared = powf(150,2);
const float shieldFriction = 0.2f;
const float shieldMassMultiplier = 2.f;
const float shieldSpeedMultiplier = 0.2f;


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
	if (mag > maxspeed)
	{
		sf::Vector2f normalize = m_direction / mag;
		m_direction = normalize*maxspeed;
	}
	this->move(m_direction*delta);

	m_direction *= 1 - friction - delta / 10;
	moveShield(delta);

    handleRope();
}

void ld::Player::draw()
{
    m_window->draw(m_shield);
    m_window->draw(m_rope);
	m_window->draw(*this);
}

void ld::Player::keyInput(const float delta)
{
	m_direction += delta * sf::Vector2f(
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) * speed,
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) -
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) * speed);
}

void ld::Player::moveShield(const float delta)
{
	sf::Vector2f dif = (*this).getPosition() - m_shield.getPosition();

	float magSquared = dif.x*dif.x + dif.y*dif.y;
	if (magSquared > ropeLenghtSquared)
	{
		m_shieldDir += (dif / magSquared) * sqrt(magSquared - ropeLenghtSquared) / shieldMassMultiplier * delta;
	}
	m_shieldDir *= 1 - shieldFriction * delta;

	m_shield.move(m_shieldDir * shieldSpeedMultiplier);
}

void ld::Player::handleRope()
{
    m_rope.setPosition(getPosition());
}
