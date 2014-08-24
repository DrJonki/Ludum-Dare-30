#include <LD30/Entity/Entity.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

ld::Entity::Entity(sf::RenderWindow &window)
: m_window(&window)
{

}

ld::Entity::~Entity()
{

}

void ld::Entity::draw()
{
	m_window->draw(*this);
}