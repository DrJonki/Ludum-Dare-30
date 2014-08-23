#pragma once

#include <LD30/GameState.hpp>
#include <array>
#include <memory>


namespace ld
{
    class BaseMenu;

    class MainMenuState : public GameState
    {
    public:

        MainMenuState();

        ~MainMenuState() final override;


        bool init() final override;

        void update(const float delta) final override;

        void draw(sf::RenderWindow& window) final override;


    private:

        enum MenuState
        {
            Main,
            Play,
            Options,
            Count
        };

        std::array<std::unique_ptr<BaseMenu>, Count> m_menus;
        MenuState m_menuState;
    };
}