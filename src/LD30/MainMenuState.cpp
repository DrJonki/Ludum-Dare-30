#include <LD30/MainMenuState.hpp>
#include <LD30/Menu/MainMenu.hpp>
#include <LD30/Menu/PlayMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <LD30/ResourceManager.hpp>
#include <LD30/Engine.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>


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
        m_menus[Main]->setDelta(1.f);

        std::array<std::unique_ptr<Button>, 3> buttons;
        for (auto& i : buttons)
        {
            i.reset(new Button(*m_window));

            // Common properties
            i->setFillColor(sf::Color(255, 255, 255, 255));
        }

        const float buttonOffset = 50.f;
        const float originxOffset = -100.f;

        /****** Options button ******/
        auto tex = ldResource.getTexture("assets/Graphics/Menus/options.png");
        buttons[1]->setTexture(tex);
        buttons[1]->setSize(sf::Vector2f(tex->getSize()) / 1.5f);
        buttons[1]->setOrigin(originxOffset, buttons[1]->getSize().y / 2.f);
        buttons[1]->setCallback([this]()
        {
            m_menuState = Options;
        });

        /****** Play button ******/
        tex = ldResource.getTexture("assets/Graphics/Menus/start.png");
        buttons[0]->setTexture(tex);
        buttons[0]->setSize(buttons[1]->getSize());
        buttons[0]->setOrigin(originxOffset, buttons[0]->getSize().y + buttonOffset + (buttons[1]->getSize().y / 2.f));
        buttons[0]->setCallback([this]()
        {
            m_menuState = Play;
        });

        /****** Exit button ******/
        tex = ldResource.getTexture("assets/Graphics/Menus/quit.png");
        buttons[2]->setTexture(tex);
        buttons[2]->setSize(buttons[1]->getSize());
        buttons[2]->setOrigin(originxOffset, -(buttonOffset + (buttons[1]->getSize().y / 2.f)));
        buttons[2]->setCallback([this]()
        {
            ld::Engine::getInstance().setShouldExit(true);
        });

        // Add all buttons to menu
        sf::Vector2f pos(0, 100.f + (1.5f * buttons[1]->getSize().y) + buttonOffset);
        //sf::Vector2f pos(0, m_window->getView().getSize().y / 2.f);
        for (auto& i : buttons)
        {
            i->setPosition(pos);
            m_menus[Main]->addElement(i.release());
        }
    }

    Button backButton(*m_window);
    auto tex = ldResource.getTexture("assets/Graphics/Menus/retry.png");
    backButton.setTexture(tex);
    backButton.setSize(sf::Vector2f(tex->getSize()));
    backButton.setOrigin(0, backButton.getSize().y);
    backButton.setPosition(100, m_window->getView().getSize().y - 100.f);
    backButton.setFillColor(sf::Color(255, 255, 255, 0));
    backButton.setCallback([this]()
    {
        m_menuState = Main;
    });

    // Play menu
    {
        m_menus[Play].reset(new PlayMenu(*m_window));

        std::array<std::unique_ptr<Button>, 2> buttons;
        for (auto& i : buttons)
        {
            i.reset(new Button(*m_window));

            i->setFillColor(sf::Color(255, 255, 255, 255));
        }

        buttons[0]->setSize(sf::Vector2f(300, 300));
        buttons[0]->setPosition(m_window->getView().getSize().x, 200);
        buttons[0]->setCallback([this]()
        {
            ld::Engine::getInstance().changeState(nullptr);
        });

        buttons[1]->setSize(sf::Vector2f(300, 300));
        buttons[1]->setPosition(buttons[0]->getPosition().x, buttons[0]->getPosition().y + 350);
        buttons[1]->setCallback([this]()
        {
            ld::Engine::getInstance().changeState(nullptr);
        });

        for (auto& i : buttons)
            m_menus[Play]->addElement(i.release());

        m_menus[Play]->addElement(new Button(backButton));
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

