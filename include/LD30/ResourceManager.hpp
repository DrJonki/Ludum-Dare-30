#pragma once

#include <unordered_map>
#include <memory>


namespace sf
{
    class Texture;
    class SoundBuffer;
}

namespace ld
{
    class ResourceManager
    {
    private:

        ResourceManager();

        ResourceManager(const ResourceManager&) = delete;

        void operator =(const ResourceManager&) = delete;

        ResourceManager(ResourceManager&&) = delete;

        void operator =(ResourceManager&&) = delete;

        ~ResourceManager();


    public:

        enum ResourceType
        {
            Texture = 1,
            SoundBuffer = 1 << 1
        };

        static ResourceManager& getInstance();

        void clearResources(ResourceType type);

        sf::Texture* getTexture(const std::string& path);

        void deleteTexture(const std::string& path);

        sf::SoundBuffer* getSoundBuffer(const std::string& path);

        void deleteSoundBuffer(const std::string& path);

    private:

        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_soundBuffers;
    };
}

#define ldResource ld::ResourceManager::getInstance()