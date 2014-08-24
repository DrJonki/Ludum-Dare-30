#include <LD30/Menu/Button.hpp>
#include <LD30/ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

ld::Button::Button(sf::RenderWindow& window)
    : Element(window)
{

}

ld::Button::~Button()
{
    while (m_sound.getStatus() == sf::Sound::Status::Playing);
}

void ld::Button::update(const float)
{
    sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));

    if (getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_sound.getStatus() != sf::Sound::Status::Playing)
            m_sound.play();

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

void ld::Button::setSound(const std::string& path)
{
    auto buffer = ldResource.getSoundBuffer(path);

    if (buffer)
        m_sound.setBuffer(*buffer);
}
