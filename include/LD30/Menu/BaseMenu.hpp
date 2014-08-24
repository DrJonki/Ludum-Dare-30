#pragma once

#include <vector>
#include <memory>


namespace sf
{
    class RenderWindow;
}

namespace ld
{
    class Element;

    class BaseMenu
    {
    public:

        BaseMenu(sf::RenderWindow& window);

        virtual ~BaseMenu() = 0;


        float getDelta();

        void setDelta(const float d);

        void offsetDelta(const float d);

        void addElement(Element* element);

        virtual void fadeInStep(const float delta) = 0;

        virtual void fadeOutStep(const float delta) = 0;

        virtual void update(const float delta) = 0;

        virtual void draw() = 0;


    private:

        float m_delta;


    protected:

        sf::RenderWindow* m_window;
        std::vector<std::unique_ptr<Element>> m_elements;
    };
}