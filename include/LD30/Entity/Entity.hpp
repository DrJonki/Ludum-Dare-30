#pragma once
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class RenderWindow;
}

namespace ld
{
	class Entity : public sf::Sprite
	{
	public:
		Entity(sf::RenderWindow &window);
		virtual ~Entity() = 0;
		virtual void update(const float dt) = 0;

	protected:
		sf::RenderWindow* m_window;
	};
}