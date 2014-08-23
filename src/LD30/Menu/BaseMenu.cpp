#include <LD30/Menu/BaseMenu.hpp>
#include <algorithm>


ld::BaseMenu::BaseMenu(sf::RenderWindow& window)
    : m_window(&window),
      m_delta(0.f)
{

}

ld::BaseMenu::~BaseMenu()
{

}

float ld::BaseMenu::getDelta()
{
    return m_delta;
}

void ld::BaseMenu::setDelta(const float d)
{
    m_delta = std::min(d, 1.0f);
    m_delta = std::max(0.f, d);
}

void ld::BaseMenu::offsetDelta(const float d)
{
    setDelta(m_delta + d);
}

void ld::BaseMenu::fadeInStep(const float delta)
{
    offsetDelta(delta);
}

void ld::BaseMenu::fadeOutStep(const float delta)
{
    offsetDelta(-delta);
}