#include <SFEX/SFEX.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <FirstScene.hpp>
#include <SecondScene.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Input");
    window.setFramerateLimit(60);

    sfex::SceneManager sceneManager;
    sceneManager.insert({"firstscene", std::make_shared<FirstScene>()});
    sceneManager.insert({"secondscene", std::make_shared<SecondScene>()});
    sceneManager.setActiveScene("firstscene");

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();
            sceneManager.onEvent(e);
        }

        sceneManager.update();
        if(sfex::Keyboard::getKeyDown(sfex::Keyboard::Key::Return))
        {
            if(sceneManager.getActiveSceneKey() == "firstscene")
                sceneManager.setActiveScene("secondscene");
            else
                sceneManager.setActiveScene("firstscene");
        }

        window.clear();

        sceneManager.render(window);

        window.display();
    }

    return 0;
}
