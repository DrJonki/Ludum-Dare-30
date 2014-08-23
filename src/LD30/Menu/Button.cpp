#include <LD30/Menu/Button.hpp>
#include <SFML/Window/Mouse.hpp>

ld::Button::Button(sf::RenderWindow& window)
    : Element(window)
{

}

ld::Button::~Button()
{

}

void ld::Button::update(const float)
{
    
}

void ld::Button::draw()
{

}

void ld::Button::setCallback(std::function<void()> callback)
{
    m_callback = callback;
}
