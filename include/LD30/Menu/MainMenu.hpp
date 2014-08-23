#include <LD30/Menu/BaseMenu.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


namespace ld
{
    class MainMenu : public BaseMenu
    {
    public:

        MainMenu(sf::RenderWindow& window);

        ~MainMenu() final override;


        void fadeInStep(const float delta) final override;

        void fadeOutStep(const float delta) final override;

        void update(const float delta) final override;

        void draw() final override;


    private:

        sf::RectangleShape m_backgroundShade;
    };
}