#include <LD30/ResourceManager.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>


ld::ResourceManager::ResourceManager()
{

}

ld::ResourceManager::~ResourceManager()
{

}



ld::ResourceManager& ld::ResourceManager::getInstance()
{
    static ResourceManager rs;
    return rs;
}

void ld::ResourceManager::clearResources(ResourceType type)
{
    if ((type & Texture) != 0)
        m_textures.clear();
    if ((type & SoundBuffer) != 0)
        m_soundBuffers.clear();
    if ((type & Font) != 0)
        m_fonts.clear();
}

sf::Texture* ld::ResourceManager::getTexture(const std::string& path)
{
    auto itr = m_textures.find(path);

    if (itr != m_textures.end())
        return itr->second.get();

    std::unique_ptr<sf::Texture> tex(new sf::Texture());

    if (!tex->loadFromFile(path))
        return nullptr;

    auto returnPointer = tex.get();
    m_textures[path].swap(tex);
    return returnPointer;
}

void ld::ResourceManager::deleteTexture(const std::string& path)
{
    auto itr = m_textures.find(path);

    if (itr != m_textures.end())
        m_textures.erase(itr);
}

sf::SoundBuffer* ld::ResourceManager::getSoundBuffer(const std::string& path)
{
    auto itr = m_soundBuffers.find(path);

    if (itr != m_soundBuffers.end())
        return itr->second.get();

    std::unique_ptr<sf::SoundBuffer> sb(new sf::SoundBuffer());

    if (!sb->loadFromFile(path))
        return nullptr;

    auto returnPointer = sb.get();
    m_soundBuffers[path].swap(sb);
    return returnPointer;
}

void ld::ResourceManager::deleteSoundBuffer(const std::string& path)
{
    auto itr = m_soundBuffers.find(path);

    if (itr != m_soundBuffers.end())
        m_soundBuffers.erase(itr);
}

sf::Font* ld::ResourceManager::getFont(const std::string& path)
{
    auto itr = m_fonts.find(path);

    if (itr != m_fonts.end())
        return itr->second.get();

    std::unique_ptr<sf::Font> font(new sf::Font());

    if (!font->loadFromFile(path))
        return nullptr;

    auto returnPointer = font.get();
    m_fonts[path].swap(font);
    return returnPointer;
}

void ld::ResourceManager::deleteFont(const std::string& path)
{
    auto itr = m_fonts.find(path);

    if (itr != m_fonts.end())
        m_fonts.erase(itr);
}

