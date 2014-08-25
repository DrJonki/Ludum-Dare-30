#include <LD30/PlayState.hpp>
#include <LD30/ResourceManager.hpp>
#include <LD30/Engine.hpp>
#include <LD30/Menu/PauseMenu.hpp>
#include <LD30/Menu/GameOverMenu.hpp>
#include <LD30/Menu/Button.hpp>
#include <LD30/MainMenuState.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <iostream>

ld::PlayState::PlayState(sf::RenderWindow& window)
	: GameState(window),
	  m_player(window),
      m_menuState(Count)
{
    m_menus[Pause].reset(new PauseMenu(*m_window));
    //m_menus[Pause]->setDelta(1.f);
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
        const float buttonOffset = 50.f;

        /****** Resume button ******/
        auto tex = ldResource.getTexture("assets/Graphics/Menus/start.png");
        buttons[0]->setTexture(tex);
        buttons[0]->setSize(sf::Vector2f(tex->getSize()) / 1.2f);
        buttons[0]->setPosition(100.f, 100.f);
        buttons[0]->setCallback([this]()
        {
            m_menuState = Count;
            Engine::getInstance().setPaused(false);
        });

        /****** Restart button ******/
        tex = ldResource.getTexture("assets/Graphics/Menus/options.png");
        buttons[1]->setTexture(tex);
        buttons[1]->setSize(buttons[0]->getSize());
        buttons[1]->setPosition(100.f, buttons[0]->getPosition().y + buttons[0]->getSize().y + buttonOffset);
        buttons[1]->setCallback([this]()
        {
            auto ptr = new PlayState(*m_window);
            ptr->setDifficulty(m_difficulty);
            Engine::getInstance().changeState(ptr);
            Engine::getInstance().setPaused(false);
        });

        /****** Exit button ******/
        tex = ldResource.getTexture("assets/Graphics/Menus/quit.png");
        buttons[2]->setTexture(tex);
        buttons[2]->setSize(buttons[1]->getSize());
        buttons[2]->setPosition(100.f, buttons[1]->getPosition().y + buttons[1]->getSize().y + buttonOffset);
        buttons[2]->setCallback([this]()
        {
            Engine::getInstance().changeState(new MainMenuState(*m_window));
            Engine::getInstance().setPaused(false);
        });

        for (auto& i : buttons)
            m_menus[Pause]->addElement(i.release());
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
	//m_player.setPosition(500.f,500.f);

	tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Shield.png");
	tex->setSmooth(true);
	m_player.m_shield.setTexture(tex);
	m_player.m_shield.setSize(sf::Vector2f(128.f, 128.f));
	m_player.m_shield.setOrigin(m_player.m_shield.getSize().x / 2, m_player.m_shield.getSize().y / 2);
	//m_player.m_shield.setPosition(m_player.getPosition() + sf::Vector2f(50.f,50.f));
	

    switch (m_difficulty)
    {
        case 2:
            m_Time = 13.f;
            m_minTime = 6.f;
            m_startLives = 4;
            break;
        case 3:
            m_Time = 10.f;
            m_minTime = 5.f;
            m_startLives = 3;
            break;
        default:
            m_Time = 15.f;
            m_minTime = 7.f;
            m_startLives = 5;
    }

	//Enemy
	addEnemy();

	return true;
}

void ld::PlayState::update(const float delta)
{
    if (Engine::getInstance().pauseButtonPressed() && !Engine::getInstance().isPaused())
    {
        Engine::getInstance().setPaused(true);
        m_menuState = Pause;
    }
/*    else if (false) // Player's lives < 1
    {
        m_menuState = GameOver;
    }
*/
	m_player.update(delta);
	collisionCheck();
	for (int i = 0; i < (int)m_enemies.size(); ++i)
	{
		m_enemies[i].setPlayer(m_player);
		m_enemies[i].update(delta);
	}
	for (std::size_t i = 0; i < m_explosions.size(); ++i)
	{
		m_explosions[i].update(delta);
		if (m_explosions[i].hasSoundStopped())
		{
			m_explosions.erase(m_explosions.begin() + i);
			--i;
		}
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
            const float orDelta = Engine::getInstance().getDeltaOverride();

            if (i == static_cast<unsigned int>(m_menuState))
                menu.fadeInStep(orDelta);
            else
                menu.fadeOutStep(orDelta);

            if (menu.getDelta() >= 0.5f)
            {
                menu.update(orDelta);
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

	for (auto &i : m_explosions)
		i.draw();
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
	ref.setSize(sf::Vector2f(148.f, 79.f));
	ref.setOrigin(ref.getSize().x / 2, ref.getSize().y / 2);
	ref.setPosition(getRandSpawnPos());
}

void ld::PlayState::countTimeForEnemies()
{
	if (m_Time <= m_spawnTime)
	{
		m_spawnTime = 0;
        std::cout << m_spawnTime << std::endl;
		addEnemy();
	}
}

void ld::PlayState::setDifficulty(int dif)
{
	m_difficulty = dif;
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
			addExplosion(m_enemies[i].getPosition());
			m_enemies.erase(m_enemies.begin() + i);
			--i;
		}
		else if (ifCollide(m_player.m_shield, m_enemies[i]))
		{
			addExplosion(m_enemies[i].getPosition());
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

void ld::PlayState::addExplosion(sf::Vector2f pos)
{
	m_explosions.emplace_back(*m_window);

	auto &ref = m_explosions.back();
	auto tex = ldResource.getTexture("assets/Graphics/Effects/Explosion_sheet.png");
	Animation anim;
	anim.load(*tex, 4);
	anim.setChangeTime(.09f);
	anim.start();
	ref.setAnimation(anim);
	ref.setTexture(tex);
	tex->setSmooth(true);
	ref.setSize(sf::Vector2f(128.f, 128.f));
	ref.setOrigin(ref.getSize().x / 2, ref.getSize().y / 2);
	ref.setPosition(pos);
}