#include <LD30/MainMenuState.hpp>
#include <LD30/Menu/MainMenu.hpp>
#include <LD30/Menu/PlayMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <LD30/ResourceManager.hpp>
#include <LD30/Engine.hpp>


ld::MainMenuState::MainMenuState(sf::RenderWindow& window)
    : GameState(window),
      m_menuState(Main)
{

}

ld::MainMenuState::~MainMenuState()
{

}

bool ld::MainMenuState::init()
{
    // Main menu
    {
        m_menus[Main].reset(new MainMenu(*m_window));

        std::array<std::unique_ptr<Button>, 3> buttons;
        for (std::size_t i = 0; i < buttons.size(); ++i)
        {
            buttons[i].reset(new Button(*m_window));

            // Common properties
            buttons[i]->setSize(sf::Vector2f(250, 200));
            buttons[i]->setFillColor(sf::Color(255, 255, 255, 255));
            buttons[i]->setPosition(100.f, 100.f + (i * (buttons[i]->getSize().y + 50.f)));
        }

        /****** Play button ******/
        buttons[0]->setTexture(ldResource.getTexture(""));
        buttons[0]->setCallback([this]()
        {
            m_menuState = Play;
        });

        /****** Options button ******/
        buttons[1]->setTexture(ldResource.getTexture(""));
        buttons[1]->setCallback([this]()
        {
            m_menuState = Options;
        });

        /****** Exit button ******/
        buttons[2]->setTexture(ldResource.getTexture(""));
        buttons[2]->setCallback([this]()
        {
            ld::Engine::getInstance().setShouldExit(true);
        });

        // Add all buttons to menu
        for (auto& i : buttons)
            m_menus[Main]->addElement(i.release());
    }

    Button backButton(*m_window);
    backButton.setTexture(ldResource.getTexture(""));
    backButton.setCallback([this]()
    {
        m_menuState = Main;
    });

    // Play menu
    {

    }

    // options menu
    {

    }

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

            if (menu.getDelta() >= 1.f)
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

