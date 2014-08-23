#pragma once

#include <LD30/Menu/BaseMenu.hpp>


namespace ld
{
    class PlayMenu : public BaseMenu
    {
        PlayMenu();

        ~PlayMenu() final override;

        bool fadeInStep(const float delta) final override;

        bool fadeOutStep(const float delta) final override;


        void update(const float delta) final override;

        void draw(sf::RenderWindow& window) final override;
    };
}