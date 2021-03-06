#include <LD30/Menu/BaseMenu.hpp>
#include <LD30/Menu/Element.hpp>
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
    m_delta = d;

    if (m_delta < 0.f)
        m_delta = 0.f;
    else if (m_delta > 1.f)
        m_delta = 1.f;
}

void ld::BaseMenu::offsetDelta(const float d)
{
    setDelta(m_delta + d);
}

void ld::BaseMenu::addElement(Element* element)
{
    if (element)
        m_elements.emplace_back(element);
}

void ld::BaseMenu::fadeInStep(const float delta)
{
    offsetDelta(delta);
}

void ld::BaseMenu::fadeOutStep(const float delta)
{
    offsetDelta(-delta);
}