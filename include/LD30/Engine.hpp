#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <LD30/Misc.hpp>
#include <LD30/Settings.hpp>
#include <memory>


namespace ld
{
    class GameState;

    class Engine
    {
    private:

        Engine();

        Engine(const Engine&) = delete;

        void operator =(const Engine&) = delete;

        Engine(Engine&&) = delete;

        void operator =(Engine&&) = delete;

        ~Engine();


    public:

        static Engine& getInstance();

        bool init();

        bool mainLoop();

        void changeState(GameState* state);

        void setShouldExit(const bool exit);

        bool isPaused();

        void setPaused(const bool paused);


    private:

        std::unique_ptr<GameState> m_currentState;
        std::unique_ptr<GameState> m_nextState;
        std::unique_ptr<sf::RenderWindow> m_window;
        bool m_paused;
        bool m_shouldExit;
    };
}