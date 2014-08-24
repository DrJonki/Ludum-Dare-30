#include <LD30/Menu/PauseMenu.hpp>
#include <LD30/Menu/Element.hpp>


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
}

void ld::PauseMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta);
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

