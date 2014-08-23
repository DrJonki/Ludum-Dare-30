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

        GameState();

        virtual ~GameState() = 0;


        virtual bool init() = 0;

        virtual void update(const float delta) = 0;

        virtual void draw(sf::RenderWindow& window) = 0;
    };
}