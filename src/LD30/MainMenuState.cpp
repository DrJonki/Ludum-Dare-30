#include <LD30/MainMenuState.hpp>
#include <LD30/Menu/MainMenu.hpp>
#include <LD30/Menu/PlayMenu.hpp>


ld::MainMenuState::MainMenuState(sf::RenderWindow& window)
    : GameState(window),
      m_menuState(Play)
{

}

ld::MainMenuState::~MainMenuState()
{

}

bool ld::MainMenuState::init()
{
    // Main menu
    m_menus[Main].reset(new MainMenu(*m_window));



    return true;
}

void ld::MainMenuState::update(const float delta)
{
    for (std::size_t i = 0; i < m_menus.size(); ++i)
    {
        if (m_menus[i])
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
}

void ld::MainMenuState::draw()
{


    for (auto& i : m_menus)
    {
        if (i)
            i->draw();
    }
}

