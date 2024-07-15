#include "gui.hpp"

#include <iostream>

#include "app/app.hpp"
#include "world/location.hpp"
#include "world/world.hpp"

#include "is_key_button_clicked_off.hpp"

typedef std::shared_ptr<PhysicalObject> PhysicalObjectPtr;

Gui::Gui()
{
    sf::Vector2f window_size = {750 * 1.7, 450 * 1.7};

    m_window.create(sf::VideoMode(window_size.x, window_size.y), "Game2",
                    sf::Style::Close);

    m_window.setFramerateLimit(100);
}

Gui*
Gui::getInstance()
{
    static Gui inst;
    return &inst;
}

sf::Vector2f
Gui::getMousePosition()
{
    sf::Vector2i m = sf::Mouse::getPosition(m_window);

    return sf::Vector2f(float(m.x), float(m.y));
}

sf::Vector2f
Gui::getWindowCentre()
{
    return {float(m_window.getSize().x) / 2.f,
            float(m_window.getSize().y) / 2.f};
}

sf::Vector2f
Gui::getWindowSize()
{
    return {float(m_window.getSize().x), float(m_window.getSize().y)};
}

void
Gui::handleEvents()
{
    handlePlayerActions();

    handleInventoryActions();

    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::EventType::Closed)
        {
            App::getInstance()->finishWork();
        }
    }
}

void
Gui::handleInventoryActions()
{
    graphic.inventory_interface.update();
}

void
Gui::handlePlayerActions()
{
    if (graphic.inventory_interface.getStatus() ==
        Graphic::InventoryInterface::Status::CLOSE)
    {
        Player::Status player_status = Player::getInstance()->getStatus();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            graphic.zoom(-App::getInstance()->getCycleTime().asSeconds());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            graphic.zoom(App::getInstance()->getCycleTime().asSeconds());

        graphic.player_interface.update();
    }

    // Player::getInstance()->handleAction(displacement_vector);
}

