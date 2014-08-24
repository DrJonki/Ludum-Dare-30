#include <LD30/Menu/Button.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
    sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));

    if (getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_callback)
            m_callback();
    }
}

void ld::Button::draw()
{
    m_window->draw(*this);
}

void ld::Button::setCallback(std::function<void()> callback)
{
    m_callback = callback;
}
