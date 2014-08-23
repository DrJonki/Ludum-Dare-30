#pragma once

#include <LD30/Menu/BaseMenu.hpp>


namespace ld
{
    class PlayMenu : public BaseMenu
    {
    public:

        PlayMenu(sf::RenderWindow& window);

        ~PlayMenu() final override;

        void fadeInStep(const float delta) final override;

        void fadeOutStep(const float delta) final override;


        void update(const float delta) final override;

        void draw() final override;
    };
}