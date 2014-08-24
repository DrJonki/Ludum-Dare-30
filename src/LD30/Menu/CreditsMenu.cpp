#include <LD30/Menu/CreditsMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <LD30/ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


ld::CreditsMenu::CreditsMenu(sf::RenderWindow& window)
    : BaseMenu(window),
      m_globalPos(window.getView().getSize().y + 200.f)
{
    sf::Texture* textures[4];
    textures[0] = ldResource.getTexture("assets/Graphics/Menus/face_meatbug.png");
    textures[1] = ldResource.getTexture("assets/Graphics/Menus/face_nyyman.png");
    textures[2] = ldResource.getTexture("assets/Graphics/Menus/face_nyyman.png");
    textures[3] = ldResource.getTexture("assets/Graphics/Menus/face_drjonki.png");

    sf::Text* texts[4];

    for (std::size_t i = 0; i < m_objects.size(); ++i)
    {
        auto& rect = m_objects[i].first;
        auto& text = m_objects[i].second;

        rect.setSize(sf::Vector2f(300, 300));
        rect.setTexture(textures[i]);
        rect.setOrigin(rect.getSize() / 2.f);
        rect.setPosition(3486255, 0);
        text.setFont(*ldResource.getFont("assets/Graphics/Roboto-Black.ttf"));
        text.setPosition(1872631, 0);
        text.setCharacterSize(60);

        texts[i] = &text;
    }

    texts[0]->setString("Asko \"Metabug\" Lahti");
    texts[1]->setString("Esko \"Eracage\" Haila");
    texts[2]->setString("Jaakko \"Nyyman\" Nikkilä");
    texts[3]->setString("Joona \"Jonki\" Tiinanen");
}

ld::CreditsMenu::~CreditsMenu()
{

}

const float stepMult = 1.2f;

void ld::CreditsMenu::fadeInStep(const float delta)
{
    BaseMenu::fadeInStep(delta * stepMult);

    static_cast<Button*>(m_elements.back().get())->setFillColor(sf::Color(255, 255, 255,
        static_cast<unsigned char>(getDelta() * 255.f)));

    for (auto& i : m_objects)
    {
        sf::Color col(255, 255, 255, static_cast<unsigned char>(getDelta() * 255.f));
        i.first.setFillColor(col);
        i.second.setColor(col);
    }
}

void ld::CreditsMenu::fadeOutStep(const float delta)
{
    BaseMenu::fadeOutStep(delta * stepMult);

    fadeInStep(0.f);
    if (getDelta() > 0.f)
        update(delta);
}

void ld::CreditsMenu::update(const float delta)
{
    for (auto& i : m_elements)
        i->update(delta);

    const float xPos = m_window->getView().getSize().x * 0.6666f;
    for (std::size_t i = 0; i < m_objects.size(); ++i)
    {
        auto& rect = m_objects[i].first;
        auto& text = m_objects[i].second;

        rect.setPosition(xPos, m_globalPos + (i * 700.f));
        text.setOrigin(text.getGlobalBounds().width / 2.f, 0);
        text.setPosition(rect.getPosition().x, rect.getPosition().y + rect.getSize().y / 2.f + 10.f);
    }

    m_globalPos -= 250.f * delta;

    if ((m_objects.back().second.getPosition().y + m_objects.back().second.getGlobalBounds().height) < 10.f)
        m_globalPos = m_window->getView().getSize().y + 200.f;
}

void ld::CreditsMenu::draw()
{
    for (auto& i : m_elements)
        i->draw();

    for (auto& i : m_objects)
    {
        m_window->draw(i.first);
        m_window->draw(i.second);
    }
}

