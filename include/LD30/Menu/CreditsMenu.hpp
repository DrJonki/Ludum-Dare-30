#pragma once

#include <LD30/Menu/BaseMenu.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>


namespace ld
{
    class CreditsMenu : public BaseMenu
    {
    public:

        CreditsMenu(sf::RenderWindow& window);

        ~CreditsMenu() final override;


        void fadeInStep(const float delta) final override;

        void fadeOutStep(const float delta) final override;

        void update(const float delta) final override;

        void draw() final override;


    private:

        float m_globalPos;
        float m_globalAlpha;
        std::array<std::pair<sf::RectangleShape, sf::Text>, 4> m_objects;

    };
}