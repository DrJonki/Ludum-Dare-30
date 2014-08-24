#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf
{
	class RenderWindow;
}

namespace ld
{
	class Entity : public sf::RectangleShape
	{
	public:
		Entity(sf::RenderWindow &window);
		virtual ~Entity() = 0;
		virtual void update(const float dt) = 0;
		virtual void draw();

	protected:
		sf::RenderWindow* m_window;
	};
}