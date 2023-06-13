#ifndef _FIRST_SCENE_HPP_
#define _FIRST_SCENE_HPP_

#include <SFEX/SFEX.hpp>
#include <SFML/Graphics.hpp>
#include <PlayerController.hpp>

class FirstScene : public sfex::Scene
{
public:
    FirstScene();

    virtual void onEvent(const sf::Event &e) override;
    virtual void start() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render(sf::RenderTarget &target) override;
    virtual void onDestroy() override;

private:
    sfex::GameObject m_player;
};

#endif // !_FIRST_SCENE_HPP_
