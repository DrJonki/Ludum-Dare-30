#pragma once


namespace sf
{
    class RenderWindow;
}

namespace ld
{
    class BaseMenu
    {
    public:

        BaseMenu();

        virtual ~BaseMenu() = 0;


        float getDelta();

        void setDelta(const float d);

        void offsetDelta(const float d);

        virtual bool fadeInStep(const float delta);

        virtual bool fadeOutStep(const float delta);

        virtual void update(const float delta) = 0;

        virtual void draw(sf::RenderWindow& window) = 0;


    private:

        float m_delta;
    };
}