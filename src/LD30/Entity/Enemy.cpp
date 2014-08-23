#include <LD30/Entity/Enemy.hpp>

ld::Enemy::Enemy(sf::RenderWindow &window)
:Entity(window),
m_player(nullptr)
{

}

ld::Enemy::~Enemy()
{

}

void ld::Enemy::update(const float /*dt*/)
{
	//TODO: update functions for Enemy
}

void ld::Enemy::setPlayer(Player &player)
{
	m_player = &player;
}