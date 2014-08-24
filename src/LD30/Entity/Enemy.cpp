#include <LD30/Entity/Enemy.hpp>
#include <LD30/Entity/Player.hpp>
#include <cmath>
#include <iostream>

ld::Enemy::Enemy(sf::RenderWindow &window)
:Entity(window),
m_player(nullptr)
{

}

ld::Enemy::~Enemy()
{

}

void ld::Enemy::update(const float delta)
{
	move(delta);
}

void ld::Enemy::setPlayer(Player &player)
{
	m_player = &player;
}

void ld::Enemy::move(const float delta)
{
	sf::Vector2f toPosition = m_player->getPosition() - this->getPosition();
	toPosition /= std::sqrt(toPosition.x*toPosition.x + toPosition.y*toPosition.y);
	const float speed = 100.f * delta;
	auto pos = this->getPosition() + (toPosition*speed);
	this->setPosition(pos);
	std::cout << "Player: " << m_player->getPosition().x << " " << m_player->getPosition().y << std::endl;
	std::cout << "Enemy: " << this->getPosition().x << " " << this->getPosition().y << std::endl;
}