#include "app.hpp"

#include <iostream>

// #include "dropped_object/dropped_object.hpp"
#include "gui/gui.hpp"
#include "gui/texture_storage.hpp"
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

    TextureStorage::getInstance()->loadAllTextures();

    Gui::getInstance()->graphic.create();

    DroppedObject::setLength(WorldCell::getLength());

    is_work = true;

    while (is_work)
    {
        cycle_time = m_clock.getElapsedTime();
        m_clock.restart();
        World::getInstance()->update();
        // std::cout << 1;

        Player::getInstance()->update();
        // std::cout << 2;
        Gui::getInstance()->graphic.display();
        // std::cout << 3;
        Gui::getInstance()->handleEvents();
        // std::cout << 4;
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