#pragma once

#include <LD30/Menu/Element.hpp>
#include <functional>


namespace ld
{
    class Button : public Element
    {
    public:

        Button(sf::RenderWindow& window);

        ~Button() final override;


        void update(const float delta) final override;

        void draw() final override;

        void setCallback(std::function<void()> callback);

    private:

        std::function<void()> m_callback;

    };
}