#include "app.hpp"

#include <iostream>

#include "gui/gui.hpp"
#include "player/player.hpp"
#include "world/location.hpp"
#include "world/world.hpp"

App::App()
{
}

App*
App::getInstance()
{
    static App m_app;
    return &m_app;
}

void
App::run()
{

    Location::setLength(5);

    World::getInstance()->setSize(51);

    World::getInstance()->generate();

    Gui::getInstance()->graphic.loadTextures();

    is_work = true;

    while (is_work)
    {
        cycle_time = m_clock.getElapsedTime();
        m_clock.restart();

        World::getInstance()->update();

        Player::getInstance()->update();

        Gui::getInstance()->graphic.display();

        Gui::getInstance()->handleEvents();
        // break;
    }
}

void
App::finishWork()
{
    is_work = false;
}

sf::Time
App::getCycleTime()
{
    return cycle_time;
}