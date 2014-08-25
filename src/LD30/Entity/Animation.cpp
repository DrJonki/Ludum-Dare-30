#include <LD30/Entity/Animation.hpp>
#include <LD30/Engine.hpp>
#include <SFML/Graphics/Texture.hpp>


ld::Animation::Animation()
    : m_clock(),
      m_size(),
      m_amount(0),
      m_changeTime(0),
      m_running(false),
      m_currentFrame(0)
{

}

ld::Animation::~Animation()
{

}

void ld::Animation::load(sf::Texture& texture, const unsigned int amount)
{
    m_amount = amount;
    m_size.y = texture.getSize().y;

    m_size.x = texture.getSize().x / amount;
}

void ld::Animation::setChangeTime(const float seconds)
{
    m_changeTime = seconds;
}

sf::IntRect ld::Animation::getRect() const
{
    if (m_running && !Engine::getInstance().isPaused())
    {
        auto passed = static_cast<unsigned int>(m_clock.getElapsedTime().asSeconds() / m_changeTime);

        if (passed > 0)
        {
            m_currentFrame += passed;
            m_currentFrame %= m_amount;

            m_clock.restart();
        }
    }

    return sf::IntRect(m_currentFrame * m_size.x, 0, m_size.x, m_size.y);
}

void ld::Animation::start()
{
    if (!m_running)
    {
        m_running = true;
        m_clock.restart();
    }
}

void ld::Animation::stop()
{
    m_running = false;
}

