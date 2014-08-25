#include <LD30/Entity/Explosion.hpp>
#include <LD30/ResourceManager.hpp>

ld::Explosion::Explosion(sf::RenderWindow &window)
:Entity(window)
{
	m_sound.setBuffer(*ldResource.getSoundBuffer("assets/Audio/Sound Effects/explosion.ogg"));
	m_sound.setLoop(false);
	m_sound.play();
}

ld::Explosion::~Explosion()
{

}

void ld::Explosion::update(const float)
{
	this->setTextureRect(m_animation.getRect());
}

void ld::Explosion::setAnimation(Animation &animation)
{
	m_animation = animation;
}

bool ld::Explosion::hasSoundStopped()
{
	return m_sound.getStatus() != sf::Sound::Status::Playing;
}