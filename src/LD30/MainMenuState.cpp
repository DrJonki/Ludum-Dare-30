#include <LD30/MainMenuState.hpp>
#include <LD30/Menu/MainMenu.hpp>
#include <LD30/Menu/PlayMenu.hpp>


ld::MainMenuState::MainMenuState()
    : m_menuState(Play)
{

}

ld::MainMenuState::~MainMenuState()
{

}

bool ld::MainMenuState::init()
{
    return true;
}

void ld::MainMenuState::update(const float delta)
{
    for (std::size_t i = 0; i < m_menus.size(); ++i)
    {
        auto& menu = *m_menus[i];

        if (i == static_cast<unsigned int>(m_menuState))
            menu.fadeInStep(delta);
        else
            menu.fadeOutStep(delta);

        if (menu.getDelta() > 0.f)
        {
            menu.update(delta);
        }
    }
}

void ld::MainMenuState::draw(sf::RenderWindow& window)
{


    for (auto& i : m_menus)
    {
        i->draw(window);
    }
}

