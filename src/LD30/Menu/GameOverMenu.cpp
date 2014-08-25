#include <LD30/Menu/GameOverMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


ld::GameOverMenu::GameOverMenu(sf::RenderWindow& window)
    : BaseMenu(window)
{
    m_shade.setSize(window.getView().getSize());
    m_shade.setFillColor(sf::Color(255, 0, 0, 0));
}

ld::GameOverMenu::~GameOverMenu()
{

}

const float stepMult = 0.8f;

void ld::GameOverMenu::fadeInStep(const float delta)
{
    BaseMenu::fadeInStep(delta * stepMult);

    m_shade.setFillColor(sf::Color(255, 0, 0, static_cast<unsigned char>(getDelta() * 80.f)));

    for (auto& i : m_elements)
        static_cast<Button*>(i.get())->setFillColor(sf::Color(255, 255, 255, static_cast<unsigned char>(getDelta() * 255.f)));
}

void ld::GameOverMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta * stepMult);

    fadeInStep(0.f);
}

void ld::GameOverMenu::update(const float delta)
{
    for (auto& i : m_elements)
        i->update(delta);
}

void ld::GameOverMenu::draw()
{
    m_window->draw(m_shade);

    for (auto& i : m_elements)
        i->draw();
}

