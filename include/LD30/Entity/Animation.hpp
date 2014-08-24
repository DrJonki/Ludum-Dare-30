#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

namespace sf
{
    class Texture;
}

namespace ld
{
    class Animation
    {
    public:

        Animation();

        ~Animation();


        void load(sf::Texture& texture, const unsigned int amount);
        
        void setChangeTime(const float seconds);

        sf::IntRect getRect() const;

        void start();

        void stop();


    private:

        mutable sf::Clock m_clock;
        sf::Vector2u m_size;
        unsigned int m_amount;
        float m_changeTime;
        bool m_running;
        mutable unsigned int m_currentFrame;

    };
}