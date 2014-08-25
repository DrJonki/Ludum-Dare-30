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
const float rubberbandStrength = 100.0f;

const float shieldDrag = 0.3f;
const float shieldFriction = 0.5f;
const float shieldMassMultiplier = 10.f;
const float shieldSpeedMultiplier = 1.f;

sf::Vector2f normalize(sf::Vector2f vec)
{
	float mag = vec.x*vec.x + vec.y*vec.y;
	sf::Vector2f retVal;

	if (mag == 0)
	{
		retVal = sf::Vector2f(0, 0);
	}
	else
	{
		retVal = sf::Vector2f(vec.x / sqrt(mag), vec.y / sqrt(mag));
	}

	return retVal;
}

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
	shieldMovement(delta);
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
		m_direction = normalize(m_direction) * maxspeed;
	}
	this->move(m_direction*delta);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
        m_direction -= normalize(m_direction) * friction * delta;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		m_direction *= 1 - drag * delta;
	}
	else
	{
		m_direction -= normalize(m_direction) * friction * delta;
		m_direction *= 1 - drag * delta;
	}
}

void ld::Player::shieldMovement(const float delta)
{
	shieldRubberband(delta);

	shieldSlow(delta);

	m_shield.move(m_shieldDir * shieldSpeedMultiplier * delta);
}

void ld::Player::shieldRubberband(const float delta)
{
	const sf::Vector2f dif = (*this).getPosition() - m_shield.getPosition();
	const float magSquared = dif.x*dif.x + dif.y*dif.y;
	const sf::Vector2f norm = dif / magSquared;

	if (magSquared > ropeLenghtSquared)
	{
		m_shieldDir += norm * sqrt(magSquared - ropeLenghtSquared) * rubberbandStrength * delta;
	}
	else if (magSquared < ropeLenghtSquared)
	{
		m_shieldDir -= norm * sqrt(ropeLenghtSquared - magSquared) * rubberbandStrength * delta;
	}
}

void ld::Player::shieldSlow(const float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		m_shieldDir -= normalize(m_shieldDir) * shieldFriction * delta;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		m_shieldDir *= 1 - shieldDrag * delta;
	}
	else
	{
		m_shieldDir -= normalize(m_shieldDir) * shieldFriction * delta;
		m_shieldDir *= 1 - shieldDrag * delta;
	}
}

int ld::Player::getLives() const
{
    return m_lives;
}

void ld::Player::setLives(const int lives)
{
    m_lives = lives;
}
