#include <LD30/PlayState.hpp>
#include <LD30/ResourceManager.hpp>
#include <LD30/Engine.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>

ld::PlayState::PlayState(sf::RenderWindow& window)
	: GameState(window),
	m_player(window)
{

}

ld::PlayState::~PlayState()
{

}

bool ld::PlayState::init()
{
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
	m_player.update(delta);
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
}

void ld::PlayState::draw()
{
	m_player.draw();
	for (auto &i:m_enemies)
	{
		i.draw();
	}
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

void ld::PlayState::collisionCheck()
{
	for (auto &i : m_enemies)
	{
		if (ifCollide(m_player, i))
		{
			//Do stuff (explosion and shit
		}
		if (ifCollide(m_player.m_shield, i))
		{
			//Aliens explode
		}
	}
}

bool ld::PlayState::ifCollide(sf::RectangleShape A, sf::RectangleShape B)
{
	float aRad = A.getGlobalBounds.getSize().y;
	float bRad = B.getGlobalBounds.getSize().y;
	float length = aRad + bRad;

	sf::Vector2f aPos = A.getPosition();
	sf::Vector2f bPos = B.getPosition();
	sf::Vector2f diff = aPos - bPos;

	float magn = diff.x*diff.x + diff.y*diff.y;

	return magn <= length;
}