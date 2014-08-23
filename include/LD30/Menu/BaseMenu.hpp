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

        BaseMenu(sf::RenderWindow& window);

        virtual ~BaseMenu() = 0;


        float getDelta();

        void setDelta(const float d);

        void offsetDelta(const float d);

        virtual void fadeInStep(const float delta);

        virtual void fadeOutStep(const float delta);

        virtual void update(const float delta) = 0;

        virtual void draw() = 0;


    private:

        float m_delta;


    protected:

        sf::RenderWindow* m_window;
    };
}