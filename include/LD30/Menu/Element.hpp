#pragma once


namespace sf
{
    class RenderWindow;
}

namespace ld
{
    class Element
    {
    public:

        Element(sf::RenderWindow& window);

        virtual ~Element() = 0;


        virtual void update(const float delta) = 0;

        virtual void draw() = 0;

    protected:

        sf::RenderWindow* m_window;

    };
}