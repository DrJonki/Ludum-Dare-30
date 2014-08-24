#pragma once


namespace sf
{
    class RenderWindow;
}

namespace ld
{
    class GameState
    {
    public:

        GameState(sf::RenderWindow& window);

        virtual ~GameState() = 0;

        virtual bool init() = 0;

        virtual void update(const float delta) = 0;

        virtual void draw() = 0;


    protected:

        sf::RenderWindow* m_window;
    };
}