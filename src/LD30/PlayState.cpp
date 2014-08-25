#include <LD30/PlayState.hpp>
#include <LD30/ResourceManager.hpp>
#include <LD30/Engine.hpp>
#include <LD30/Menu/PauseMenu.hpp>
#include <LD30/Menu/GameOverMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <iostream>

ld::PlayState::PlayState(sf::RenderWindow& window)
	: GameState(window),
	  m_player(window),
      m_menuState(Pause)
{
    m_menus[Pause].reset(new PauseMenu(*m_window));
    m_menus[Pause]->setDelta(1.f);
    m_menus[GameOver].reset(new GameOverMenu(*m_window));
}

ld::PlayState::~PlayState()
{

}

bool ld::PlayState::init()
{
    if (m_music.openFromFile("assets/Audio/Music/Abstraction - Ludum Dare 28 - First Track.wav"))
        m_music.play();
    m_music.setLoop(true);

    // Pause menu
    {
        std::array<std::unique_ptr<Button>, 3> buttons;

        for (auto& i : buttons)
        {
            i.reset(new Button(*m_window));

            i->setFillColor(sf::Color(255, 255, 255, 255));
            i->setSound("assets/Audio/Sound Effects/menuselect.ogg");
        }


    }

    // Game over menu
    {

    }

	//Player
	auto tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Player_Base.png");
	tex->setSmooth(true);
	m_player.setTexture(tex);
	m_player.setSize(sf::Vector2f(128.f,128.f));
	m_player.setOrigin(m_player.getSize().x / 2, m_player.getSize().y / 2);

	tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Shield.png");
	tex->setSmooth(true);
	m_player.m_shield.setTexture(tex);
	m_player.m_shield.setSize(sf::Vector2f(128.f, 128.f));
	m_player.m_shield.setOrigin(m_player.m_shield.getSize().x / 2, m_player.m_shield.getSize().y / 2);
	
	//Enemy
	addEnemy();

	return true;
}

void ld::PlayState::update(const float delta)
{
    if (Engine::getInstance().pauseButtonPressed())
    {
        Engine::getInstance().setPaused(!Engine::getInstance().isPaused());
    }

	m_player.update(delta);
	collisionCheck();
	for (int i = 0; i < (int)m_enemies.size(); ++i)
	{
		m_enemies[i].setPlayer(m_player);
		m_enemies[i].update(delta);
	}

	m_spawnTime += delta;
	countTimeForEnemies();
	if (m_Time > m_minTime)
		m_Time -= delta / 100;
	else
		m_Time = m_minTime;

    for (std::size_t i = 0; i < m_menus.size(); ++i)
    {
        if (m_menus[i])
        {
            auto& menu = *m_menus[i];

            if (i == static_cast<unsigned int>(m_menuState))
                menu.fadeInStep(delta);
            else
                menu.fadeOutStep(delta);

            if (menu.getDelta() >= 0.5f)
            {
                menu.update(delta);
            }
        }
    }
}

void ld::PlayState::draw()
{
	m_player.draw();
	for (auto &i:m_enemies)
	{
		i.draw();
	}

    for (auto& i : m_menus)
        i->draw();
}

void ld::PlayState::addEnemy()
{
	m_enemies.emplace_back(*m_window);
	auto& ref = m_enemies.back();

	if (!easterEgg)
	{
		auto tex = ldResource.getTexture("assets/Graphics/Enemies/Alien_1_sheet.png");
		Animation anim;
		anim.load(*tex, 3);
		anim.setChangeTime(0.5f);
		anim.start();
		ref.setAnimation(anim);
		ref.setTexture(tex);
		tex->setSmooth(true);
	}
	else
	{
		auto tex = ldResource.getTexture("assets/Graphics/Enemies/space core.png");
		Animation anim;
		anim.load(*tex, 1);
		anim.setChangeTime(1);
		anim.start();
		ref.setTexture(tex);
		tex->setSmooth(true);
		ref.m_useAnim = false;
		easterEgg = false;
	}
	ref.setSize(sf::Vector2f(256.f, 148.f));
	ref.setOrigin(ref.getSize().x / 2, ref.getSize().y / 2);
	ref.setPosition(getRandSpawnPos());
}

void ld::PlayState::countTimeForEnemies()
{
	if (m_Time <= m_spawnTime)
	{
		m_spawnTime = 0;
		addEnemy();
	}
}

void ld::PlayState::setDifficulty(int dif)
{
	switch (dif)
	{
	case 1:
		m_Time = 15.f;
		m_minTime = 7.f;
		startLives = 5;
		break;
	case 2:
		m_Time = 13.f;
		m_minTime = 6.f;
		startLives = 4;
		break;
	case 3:
		m_Time = 10.f;
		m_minTime = 5.f;
		startLives = 3;
		break;
    default:
        m_Time = 15.f;
        m_minTime = 7.f;
        startLives = 5;
	}
}

sf::Vector2f ld::PlayState::getRandSpawnPos()
{
	auto &ref = m_window->getView();

	int east = ld::Misc::getRandomInt(1, 999);
	if (east == 556)
		easterEgg = true;

	switch (ld::Misc::getRandomInt(1, 4))
	{
	case 1: //Left
		return sf::Vector2f(-300,ld::Misc::getRandomFloat(0,ref.getSize().y));
		break;
	case 2: //Right
		return sf::Vector2f(ref.getSize().x + 300, ld::Misc::getRandomFloat(0, ref.getSize().y));
		break;
	case 3: //Top
		return sf::Vector2f(ld::Misc::getRandomFloat(0, ref.getSize().x), -ref.getSize().y - 300);
		break;
	case 4: //Bottom
		return sf::Vector2f(ld::Misc::getRandomFloat(0, ref.getSize().y), ref.getSize().y + 300);
		break;
	}
	return sf::Vector2f(0,0);
}

// Prototype
bool ifCollide(const sf::RectangleShape&, const sf::RectangleShape&);

void ld::PlayState::collisionCheck()
{
	//for (auto &i : m_enemies)
	for (std::size_t i = 0; i < m_enemies.size(); ++i)
	{
		if (ifCollide(m_player, m_enemies[i]))
		{
			//Do stuff (explosion and shit
			std::cout << "OUCH" << std::endl;
		}
		if (ifCollide(m_player.m_shield, m_enemies[i]))
		{
			m_enemies.erase(m_enemies.begin() + i);
			--i;
			std::cout << "BANG" << std::endl;
			//Aliens explode
		}
	}
}

bool ifCollide(const sf::RectangleShape& A, const sf::RectangleShape& B)
{
	float aRad = A.getGlobalBounds().height;
	float bRad = B.getGlobalBounds().height;
	float length = (aRad + bRad)/2.f;

	sf::Vector2f aPos = A.getPosition();
	sf::Vector2f bPos = B.getPosition();
	sf::Vector2f diff = aPos - bPos;

	float magn = sqrt(diff.x*diff.x + diff.y*diff.y);

	return magn <= length;
}