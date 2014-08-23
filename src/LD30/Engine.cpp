#include <LD30/Engine.hpp>
#include <LD30/MainMenuState.hpp>
#include <SFML/Window/Event.hpp>


namespace
{
    sf::RenderWindow* openWindow()
    {
        int x = ld::Settings::getInt("iResolutionX", 1024);
        int y = ld::Settings::getInt("iResolutionY", 600);

        auto wndw = new sf::RenderWindow(sf::VideoMode(x, y),
                                         ld::Settings::getString("sWindowTitle", "You haven't set the window title :("), sf::Style::Close);

        sf::Vector2f wsize(wndw->getSize());
        wndw->setView(sf::View(wsize / 2.f, sf::Vector2f(1920.f, 1080.f)));
        
        return wndw;
    }
}

ld::Engine::Engine()
    : m_currentState      (nullptr),
      m_nextState         (nullptr),
      m_window            (nullptr),
      m_paused            (false),
      m_shouldExit        (false)
{

}

ld::Engine::~Engine()
{

}



ld::Engine& ld::Engine::getInstance()
{
    static Engine eng;
    return eng;
}

bool ld::Engine::init()
{
    ld::Settings::init(ld::Misc::getHomeDir("LD30") + "settings.json");

    m_window.reset(openWindow());
    
    m_currentState.reset(new MainMenuState());

    return (m_window->isOpen() && m_currentState);
}

bool ld::Engine::mainLoop()
{
    sf::Clock frameClock;

    while (!m_shouldExit)
    {
        // If changeState has been called, the current state will be removed & deleted and replaced with the new one.
        if (m_nextState)
        {
            m_currentState.reset(m_nextState.release());
            m_currentState->init();
        }

        // Call update.
        m_currentState->update(m_paused ? 0.f : frameClock.restart().asSeconds());

        // Draw
        m_window->clear();
        m_currentState->draw(*m_window);
        m_window->display();

        // Poll events
        sf::Event e;
        while (m_window->pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                m_shouldExit = true;
        }
    }

    ld::Settings::writeSettings();

    return true;
}

void ld::Engine::changeState(GameState* state)
{
    m_nextState.reset(state);
}

void ld::Engine::setShouldExit(const bool exit)
{
    m_shouldExit = exit;
}
