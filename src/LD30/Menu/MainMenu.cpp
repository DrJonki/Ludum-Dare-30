#include <LD30/Menu/MainMenu.hpp>


ld::MainMenu::MainMenu()
{

}

ld::MainMenu::~MainMenu()
{

}

bool ld::MainMenu::fadeInStep(const float delta)
{
    if (BaseMenu::fadeInStep(delta))
        return true;



    return false;
}

bool ld::MainMenu::fadeOutStep(const float delta)
{
    if (BaseMenu::fadeOutStep(delta))
        return true;



    return false;
}

void ld::MainMenu::update(const float)
{

}

void ld::MainMenu::draw(sf::RenderWindow&)
{

}