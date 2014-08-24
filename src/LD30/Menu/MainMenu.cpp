#include <LD30/Menu/MainMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <LD30/Misc.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>


ld::MainMenu::MainMenu(sf::RenderWindow& window)
    : BaseMenu(window),
      m_backgroundShade(window.getView().getSize())
{
    m_backgroundShade.setFillColor(sf::Color(0, 0, 0, 0));
}

ld::MainMenu::~MainMenu()
{

}

void ld::MainMenu::fadeInStep(const float delta)
{
    BaseMenu::fadeInStep(delta);

    const float min = 0.75f;
    const float scale = min + (std::abs(std::sinf(getDelta() * ld::pi * 0.5f)) * (1.f - min));
    for (auto& i : m_elements)
        static_cast<Button*>(i.get())->setScale(scale, scale);

    m_backgroundShade.setFillColor(sf::Color(0, 0, 0, static_cast<char>(128.f - 128.f * getDelta())));
}

void ld::MainMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta);

    fadeInStep(0.f);
}

void ld::MainMenu::update(const float delta)
{

    for (auto& i : m_elements)
        i->update(delta);
}

void ld::MainMenu::draw()
{
    

    for (auto& i : m_elements)
        i->draw();

    m_window->draw(m_backgroundShade);
}