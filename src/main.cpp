#include <LD30/Engine.hpp>
#include <SFML/Main.hpp>

bool main()
{
    return (ld::Engine::getInstance().init() && ld::Engine::getInstance().mainLoop());
}