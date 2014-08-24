#include <LD30/Menu/MainMenu.hpp>
#include <LD30/Menu/Element.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


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
}

void ld::MainMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta);
}

void ld::MainMenu::update(const float delta)
{
    for (auto& i : m_elements)
        i->update(delta);
}

void ld::MainMenu::draw()
{
    m_window->draw(m_backgroundShade);

    for (auto& i : m_elements)
        i->draw();
}