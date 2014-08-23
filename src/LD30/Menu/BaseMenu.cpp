#include <LD30/Menu/BaseMenu.hpp>
#include <algorithm>


ld::BaseMenu::BaseMenu()
    : m_delta(0)
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

bool ld::BaseMenu::fadeInStep(const float delta)
{
    const auto oldDelta = m_delta;

    offsetDelta(delta);

    return oldDelta >= 1.f;
}

bool ld::BaseMenu::fadeOutStep(const float delta)
{
    const auto oldDelta = m_delta;

    offsetDelta(-delta);

    return oldDelta <= 0.f;
}