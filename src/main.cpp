#include <SFML/Graphics.hpp>
#include <LD30/Misc.hpp>
#include <LD30/Settings.hpp>

int main()
{
    ld::Settings::init(ld::Misc::getHomeDir("LD30") + "settings.json");

    sf::RenderWindow window(sf::VideoMode(ld::Settings::getInt("iResolutionX", 1024), ld::Settings::getInt("iResolutionY", 600)),
                            ld::Settings::getString("sWindowTitle", "You haven't set the window title :("));



    ld::Settings::writeSettings();

    return 0;
}