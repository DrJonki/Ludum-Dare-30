#pragma once

#include <LD30/Entity/Entity.hpp>
#include <LD30/Entity/Animation.hpp>
#include <SFML/Audio/Sound.hpp>

namespace ld
{
	class Explosion : public Entity
	{
	public:
		Explosion(sf::RenderWindow &window);
		~Explosion();
		void update(const float dt) final override;
		void setAnimation(Animation &animation);
		bool hasSoundStopped();
	private:
		Animation m_animation;
		sf::Sound m_sound;
	};
}