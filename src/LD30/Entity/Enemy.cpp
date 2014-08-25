#include <LD30/Entity/Enemy.hpp>
#include <LD30/Entity/Player.hpp>
#include <cmath>
#include <iostream>

ld::Enemy::Enemy(sf::RenderWindow &window)
:Entity(window),
m_player(nullptr),
m_useAnim(true)
{

}

ld::Enemy::~Enemy()
{

}

void ld::Enemy::update(const float delta)
{
	move(delta);
	if (m_useAnim)
		this->setTextureRect(m_animation.getRect());
}

void ld::Enemy::setPlayer(Player* player)
{
	m_player = player;
}

void ld::Enemy::setAnimation(Animation &animation)
{
	m_animation = animation;
}

void ld::Enemy::move(const float delta)
{
    if (m_player)
    {
        sf::Vector2f toPosition = m_player->getPosition() - this->getPosition();
        toPosition /= std::sqrt(toPosition.x*toPosition.x + toPosition.y*toPosition.y);
        const float speed = 50.f * delta;
        auto pos = this->getPosition() + (toPosition*speed);
        this->setPosition(pos);
    }
}