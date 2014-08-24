#include <LD30/Menu/PlayMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


ld::PlayMenu::PlayMenu(sf::RenderWindow& window)
    : BaseMenu(window)
{

}

ld::PlayMenu::~PlayMenu()
{

}

void ld::PlayMenu::fadeInStep(const float delta)
{
    BaseMenu::fadeInStep(delta);

    for (std::size_t i = 0; i < m_elements.size() - 1; ++i)
    {
        auto but = static_cast<Button*>(m_elements[i].get());
        static const sf::Vector2f startPos = but->getPosition();
        static const float basePos = m_window->getView().getSize().x * 0.666666f;
        static const float difference = startPos.x - basePos;

        but->setPosition(std::max(basePos, startPos.x - (getDelta() * difference) + (i * 75.f)),
                         but->getPosition().y);
        but->setFillColor(sf::Color(255, 255, 255, static_cast<char>(getDelta() * 255.f)));
    }

    static_cast<Button*>(m_elements.back().get())->setFillColor(sf::Color(255, 255, 255, static_cast<char>(getDelta() * 255.f)));
}

void ld::PlayMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta);

    fadeInStep(0.f);
}

void ld::PlayMenu::update(const float delta)
{
    for (auto& i : m_elements)
    {
        i->update(delta);
    }
}

void ld::PlayMenu::draw()
{
    for (auto& i : m_elements)
        i->draw();
}