#include <LD30/Menu/PlayMenu.hpp>


ld::PlayMenu::PlayMenu()
{

}

ld::PlayMenu::~PlayMenu()
{

}

bool ld::PlayMenu::fadeInStep(const float delta)
{
    if (BaseMenu::fadeInStep(delta))
        return true;



    return false;
}

bool ld::PlayMenu::fadeOutStep(const float delta)
{
    if (BaseMenu::fadeOutStep(delta))
        return true;



    return false;
}

void ld::PlayMenu::update(const float)
{

}

void ld::PlayMenu::draw(sf::RenderWindow&)
{

}