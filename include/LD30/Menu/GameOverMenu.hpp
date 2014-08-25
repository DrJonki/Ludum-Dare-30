#pragma once

#include <LD30/Menu/BaseMenu.hpp>


namespace ld
{
    class GameOverMenu : public BaseMenu
    {
    public:

        GameOverMenu(sf::RenderWindow& window);

        ~GameOverMenu() final override;


        void fadeInStep(const float delta) final override;

        void fadeOutStep(const float delta) final override;

        void update(const float delta) final override;

        void draw() final override;

    };
}