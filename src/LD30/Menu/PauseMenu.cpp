#include <LD30/Menu/PauseMenu.hpp>
#include <LD30/Menu/Button.hpp>


ld::PauseMenu::PauseMenu(sf::RenderWindow& window)
    : BaseMenu(window)
{

}

ld::PauseMenu::~PauseMenu()
{

}

void ld::PauseMenu::fadeInStep(const float delta)
{
    BaseMenu::fadeInStep(delta);

    for (auto& i : m_elements)
        static_cast<Button*>(i.get())->setFillColor(sf::Color(255, 255, 255, static_cast<unsigned char>(getDelta() * 255.f)));
}

void ld::PauseMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta);

    fadeInStep(0.f);
}

void ld::PauseMenu::update(const float delta)
{
    for (auto& i : m_elements)
        i->update(delta);
}

void ld::PauseMenu::draw()
{
    for (auto& i : m_elements)
        i->draw();
}

