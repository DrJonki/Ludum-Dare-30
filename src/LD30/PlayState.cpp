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

#include <cassert>

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
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    if (m_music.openFromFile("assets/Audio/Music/Abstraction - Ludum Dare 28 - First Track.wav"))
        m_music.play();
    m_music.setLoop(true);

    const float buttonScale = 2.f;
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
        auto tex = ldResource.getTexture("assets/Graphics/Menus/retry.png");
        buttons[0]->setTexture(tex);
        buttons[0]->setSize(sf::Vector2f(tex->getSize()) * buttonScale);
        buttons[0]->setPosition(100.f, 100.f);
        buttons[0]->setCallback([this]()
        {
            m_menuState = Count;
            Engine::getInstance().setPaused(false);
        });

        /****** Restart button ******/
        tex = ldResource.getTexture("assets/Graphics/Menus/restart.png");
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
        tex = ldResource.getTexture("assets/Graphics/Menus/backToMenu.png");
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
        std::array<std::unique_ptr<Button>, 2> buttons;

        for (auto& i : buttons)
        {
            i.reset(new Button(*m_window));

            i->setFillColor(sf::Color(255, 255, 255, 255));
            i->setSound("assets/Audio/Sound Effects/menuselect.ogg");
        }

        const float buttonOffset = 50.f;

        /****** Restart button ******/
        auto tex = ldResource.getTexture("assets/Graphics/Menus/restart.png");
        buttons[0]->setTexture(tex);
        buttons[0]->setSize(sf::Vector2f(tex->getSize()) * buttonScale);
        buttons[0]->setPosition(100.f, 100.f);
        buttons[0]->setCallback([this]()
        {
            auto ptr = new PlayState(*m_window);
            ptr->setDifficulty(m_difficulty);

            Engine::getInstance().changeState(ptr);
            Engine::getInstance().setPaused(false);
        });

        /****** Quit button ******/
        tex = ldResource.getTexture("assets/Graphics/Menus/backToMenu.png");
        buttons[1]->setTexture(tex);
        buttons[1]->setSize(buttons[0]->getSize());
        buttons[1]->setPosition(100.f, buttons[0]->getPosition().y + buttons[0]->getSize().y + buttonOffset);
        buttons[1]->setCallback([this]()
        {
            Engine::getInstance().changeState(new MainMenuState(*m_window));
            Engine::getInstance().setPaused(false);
        });

        for (auto& i : buttons)
            m_menus[GameOver]->addElement(i.release());
    }

	//Player
	auto tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Player_Base.png");
	tex->setSmooth(true);
	m_player.setTexture(tex);
	m_player.setSize(sf::Vector2f(128.f,128.f));
	m_player.setOrigin(m_player.getSize().x / 2, m_player.getSize().y / 2);
	m_player.setPosition(m_window->getView().getCenter());

	tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Shield.png");
	tex->setSmooth(true);
	m_player.m_shield.setTexture(tex);
	m_player.m_shield.setSize(sf::Vector2f(128.f, 128.f));
	m_player.m_shield.setOrigin(m_player.m_shield.getSize().x / 2, m_player.m_shield.getSize().y / 2);
	m_player.m_shield.setPosition(m_player.getPosition() - m_player.getSize());

	tex = ldResource.getTexture("assets/Graphics/Effects/electricity_chain_loop.png");
	tex->setSmooth(true);
	tex->setRepeated(true);
	m_player.m_chain.setTexture(tex);
	m_player.m_chain.setSize(sf::Vector2f(200, 200));
	m_player.m_chain.setOrigin(m_player.m_chain.getSize().x / 2, 0);
	m_player.m_chain.setPosition(m_player.getPosition());

    tex = ldResource.getTexture("assets/Graphics/Player and shield planets/Player_Cloud.png");
    tex->setSmooth(true);
    m_player.m_clouds.setTexture(tex);
    m_player.m_clouds.setSize(m_player.getSize());
    m_player.m_clouds.setScale(m_player.getScale());
    m_player.m_clouds.setOrigin(m_player.getSize() / 2.f);
    m_player.m_clouds.setPosition(m_player.getPosition());
	
    tex = ldResource.getTexture("assets/Graphics/Backgrounds/background.png");
    tex->setSmooth(true);
    m_background.setSize(m_window->getView().getSize());
    m_background.setTexture(tex);

    tex = ldResource.getTexture("assets/Graphics/Menus/healthcounter.png");
    tex->setSmooth(true);
    m_lifeIcon.setTexture(tex);
    m_lifeIcon.setSize(sf::Vector2f(m_lifeIcon.getTexture()->getSize()));

    tex = ldResource.getTexture("assets/Graphics/Menus/killcounter.png");
    tex->setSmooth(true);
    m_killIcon.setTexture(tex);
    m_killIcon.setSize(sf::Vector2f(m_killIcon.getTexture()->getSize()));

    auto font = ldResource.getFont("assets/Graphics/Roboto-Black.ttf");
    m_scoreText.setFont(*font);
    m_scoreText.setCharacterSize(50);
    m_scoreText.setColor(sf::Color(255, 255, 255, 255));

    m_killsText.setFont(*font);
    m_killsText.setCharacterSize(65);
    m_killsText.setColor(sf::Color(255, 255, 255, 255));

    switch (m_difficulty)
    {
        case 1:
            m_Time = 6.f;
            m_minTime = 3.f;
			m_player.setLives(5);
			m_enemySpeed = 150.f;
			m_enemySpeedMin = 100.f;
			break;
        case 2:
            m_Time = 3.5f;
            m_minTime = 1.f;
            m_player.setLives(4);
			m_enemySpeed = 185.f;
			m_enemySpeedMin = 100.f;
            break;
        case 3:
            m_Time = 2.5f;
            m_minTime = 0.25f;
			m_player.setLives(3);
			m_enemySpeed = 225.f;
			m_enemySpeedMin = 100.f;
            break;
		default:
			assert(false);
			break;
    }

    m_scoreClock.restart();

	//Enemy
	addEnemy();

	return true;
}

void ld::PlayState::update(const float delta)
{
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        m_player.setLives(0);
    }
*/
    if (Engine::getInstance().pauseButtonPressed() && !Engine::getInstance().isPaused())
    {
        Engine::getInstance().setPaused(true);
        m_menuState = Pause;
    }
    else if (m_player.getLives() < 1)
    {
        m_menuState = GameOver;
    }

    if (Engine::getInstance().isPaused())
        m_scoreClock.restart();
    else if (m_scoreClock.getElapsedTime().asSeconds() > 10.f)
    {
        ++m_score;
        m_scoreClock.restart();
    }

	m_player.update(delta);
	collisionCheck();
	for (int i = 0; i < (int)m_enemies.size(); ++i)
	{
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
    m_window->draw(m_background);

    if (m_player.getLives() > 0)
	    m_player.draw();

	for (auto &i:m_enemies)
	{
		i.draw();
	
    }

    for (auto &i : m_explosions)
        i.draw();

    for (auto& i : m_menus)
        i->draw();

    if (m_menuState == Count)
    {
        const float firstPos = 10.f;
        const float offset = 10.f;
        float lastPos = 0.f;

        for (int i = 0; i < m_player.getLives(); ++i)
        {
            m_lifeIcon.setPosition(lastPos = (firstPos + (i * (m_lifeIcon.getGlobalBounds().width + offset)) + offset), firstPos);
            m_window->draw(m_lifeIcon);
        }

        m_killIcon.setPosition(lastPos + m_lifeIcon.getGlobalBounds().width + offset * 8.f, firstPos);
        m_killIcon.setFillColor(sf::Color(255, 255, 255, 255));
        m_killIcon.setScale(1.f, 1.f);
        m_window->draw(m_killIcon);

        m_scoreText.setString("Score: " + std::to_string(m_score));
        m_scoreText.setPosition(firstPos + offset * 2.f, m_lifeIcon.getPosition().y + m_lifeIcon.getGlobalBounds().height + offset);
        m_scoreText.setColor(sf::Color(255, 255, 255, 255));
        m_scoreText.setScale(1.f, 1.f);
        m_window->draw(m_scoreText);

        m_killsText.setString(std::to_string(m_kills));
        m_killsText.setOrigin(m_killsText.getGlobalBounds().width / 2.f, m_killsText.getGlobalBounds().height / 2.f);
        m_killsText.setPosition(m_killIcon.getPosition().x + m_killIcon.getGlobalBounds().width + offset * 4.f,
                                m_killIcon.getPosition().y + m_killIcon.getGlobalBounds().height / 2.f - offset * 2.f);
        m_killsText.setColor(sf::Color(255, 255, 255, 255));
        m_killsText.setScale(1.f, 1.f);
        m_window->draw(m_killsText);
    }
    else if (m_menuState == GameOver)
    {
        m_killIcon.setScale(2.f, 2.f);
        const float menuDelta = m_menus[GameOver]->getDelta();
        m_killIcon.setFillColor(sf::Color(255, 255, 255, static_cast<unsigned char>(menuDelta * 255.f)));
        m_killsText.setScale(2.f, 2.f);
        m_killsText.setColor(sf::Color(255, 255, 255, static_cast<unsigned char>(menuDelta * 255.f)));
        m_scoreText.setScale(2.f, 2.f);
        m_scoreText.setColor(sf::Color(255, 255, 255, static_cast<unsigned char>(menuDelta * 255.f)));

        m_killIcon.setPosition(500, 150);
        m_killsText.setPosition(800, 240);
        m_scoreText.setPosition(500, 500);

        m_window->draw(m_killIcon);
        m_window->draw(m_killsText);
        m_window->draw(m_scoreText);
    }
}

void ld::PlayState::addEnemy()
{
    if (m_player.getLives() < 1)
        return;
        
    m_enemies.emplace_back(*m_window, Misc::getRandomFloat(m_enemySpeedMin, m_enemySpeed));
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
    ref.setPlayer(&m_player);
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
		return sf::Vector2f(ld::Misc::getRandomFloat(0, ref.getSize().x), -300);
		break;
	case 4: //Bottom
		return sf::Vector2f(ld::Misc::getRandomFloat(0, ref.getSize().x), ref.getSize().y + 300);
		break;
	}
	return sf::Vector2f(0,0);
}

// Prototype
bool ifCollide(const sf::RectangleShape&, const sf::RectangleShape&);

void ld::PlayState::collisionCheck()
{
    if (m_player.getLives() < 1)
        return;

	//for (auto &i : m_enemies)
	for (std::size_t i = 0; i < m_enemies.size(); ++i)
	{
		if (ifCollide(m_player, m_enemies[i]))
		{
			addExplosion(m_enemies[i].getPosition());
			m_enemies.erase(m_enemies.begin() + i);
			--i;
            m_player.setLives(m_player.getLives() - 1);

            if (m_player.getLives() < 1)
            {
                addExplosion(m_player.getPosition());
                
                for (auto& i : m_enemies)
                    i.setPlayer(nullptr);

                break;
            }
		}
		else if (ifCollide(m_player.m_shield, m_enemies[i]))
		{
			addExplosion(m_enemies[i].getPosition());
			m_enemies.erase(m_enemies.begin() + i);
			--i;
            m_score += m_difficulty;
            ++m_kills;
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
	anim.setLooping(false);
	anim.start();
	ref.setAnimation(anim);
	ref.setTexture(tex);
	tex->setSmooth(true);
	ref.setSize(sf::Vector2f(128.f, 128.f));
	ref.setOrigin(ref.getSize().x / 2, ref.getSize().y / 2);
	ref.setPosition(pos);
}