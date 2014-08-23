#include <LD30/Menu/MainMenu.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


ld::MainMenu::MainMenu(sf::RenderWindow& window)
    : BaseMenu(window),
      m_backgroundShade(window.getView().getSize())
{

}

ld::MainMenu::~MainMenu()
{

}

void ld::MainMenu::fadeInStep(const float delta)
{
    BaseMenu::fadeInStep(delta);
}

void ld::MainMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta);
}

void ld::MainMenu::update(const float)
{

}

void ld::MainMenu::draw()
{
    m_window->draw(m_backgroundShade);
}