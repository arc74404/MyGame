#include <iostream>

#include "world/location.hpp"
#include "world/world.hpp"

#include "gui.hpp"

void
Gui::Graphic::PlayerInterface::update()
{
    sf::Vector2f displacement_vector =
        Gui::getInstance()->getMousePosition() -
        Gui::getInstance()->graphic.getPlayerPositionInWindow();

    displacement_vector.x /= Gui::getInstance()->graphic.getScope();
    displacement_vector.y /= Gui::getInstance()->graphic.getScope();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Player::getInstance()->moveNextPosition(displacement_vector);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        Player::getInstance()->stopMoving();
        sf::Vector2f poke_coordinate =
            Player::getInstance()->getPosition() + displacement_vector;

        const Location& l = World::getInstance()->getLocation(poke_coordinate);

        int loc_size = Location::getLength() * WorldCell::getLength();

        const WorldCell& world_cell =
            l.getCell({float(int(poke_coordinate.x) % loc_size),
                       float(int(poke_coordinate.y) % loc_size)});

        const StorageCell& using_storage_cell =
            Gui::getInstance()
                ->graphic.inventory_interface.getUsingStorageCellRef();

        Player::getInstance()->operate(world_cell, using_storage_cell);
    }
}

void
Gui::Graphic::PlayerInterface::loadTextures()
{
    float cell_length = WorldCell::getLength();

    hero_texture.loadFromFile("C:/Users/arsbo/source/repos/game2/"
                              "resources/hero.png");

    hero_shape.setTexture(hero_texture.getTexturePtr());

    sf::Vector2i texture_rect_size = {17, 31};
    sf::Vector2i texture_rect_pos  = {10, 2};

    hero_texture[Player::Status::STAND].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size));

    texture_rect_size = {20, 31};

    texture_rect_pos.x += 34;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 0

    texture_rect_pos.x += 36;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 1

    texture_rect_pos.x += 34;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 2

    texture_rect_pos.x += 36;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 3

    texture_rect_pos.x += 36;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 4

    texture_rect_pos.x += 34;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 5

    health_indicator.create();
    hunger_indicator.create();

    health_indicator.setDesignation("health");
    hunger_indicator.setDesignation("hunger");

    health_indicator.setColor(sf::Color::Red);
    hunger_indicator.setColor(sf::Color::Yellow);

    left_corner.setFillColor(sf::Color(255, 255, 255, 140));
}

void
Gui::Graphic::PlayerInterface::drawPlayer()
{
    sf::Vector2u window_size     = Gui::getInstance()->m_window.getSize();
    Player::Status player_status = Player::getInstance()->getStatus();
    int rect_index;

    sf::IntRect r;

    switch (player_status)
    {

        case Player::Status::STAND:
            r = hero_texture[player_status][0];

            if (Player::getInstance()->getFlank() == Player::Flank::LEFT)
            {
                r.left += r.width;
                r.width *= -1;
            }
            hero_shape.setTextureRect(r);

            break;

        case Player::Status::WALK:

            rect_index =
                (int(Player::getInstance()->getWalkTimeSeconds() * 1000) / 50) %
                hero_texture[Player::Status::WALK].size();

            r = hero_texture[player_status][rect_index];

            if (Player::getInstance()->getFlank() == Player::Flank::LEFT)
            {
                r.left += r.width;
                r.width *= -1;
            }
            hero_shape.setTextureRect(r);
            break;

        default:
            break;
    }
    Gui::getInstance()->m_window.draw(hero_shape);
}

void
Gui::Graphic::PlayerInterface::drawInterface()
{
    sf::Vector2u window_size = Gui::getInstance()->m_window.getSize();
    sf::Vector2f shape_size  = {window_size.x * 0.3f, window_size.y * 0.05f};
    sf::Vector2f shape_position1 = {window_size.y * 0.03f,
                                    window_size.y * 0.03f};

    int procent_health = Player::getInstance()->getProcentHealth() * 100;
    int procent_hunger = Player::getInstance()->getProcentHunger() * 100;

    health_indicator.setPosition(shape_position1);
    health_indicator.setSize(shape_size);
    health_indicator.setProcent(procent_health);

    sf::Vector2f shape_position2 = {shape_position1.x,
                                    shape_position1.y + shape_size.y +
                                        window_size.y * 0.05f};

    hunger_indicator.setPosition(shape_position2);
    hunger_indicator.setSize(shape_size);
    hunger_indicator.setProcent(procent_hunger);

    sf::Vector2f left_corner_size = {
        shape_size.x, shape_position2.y + shape_size.y - shape_position1.y};

    left_corner.setSize(left_corner_size);
    left_corner.setPosition(shape_position1);

    Gui::getInstance()->m_window.draw(left_corner);

    health_indicator.draw();
    hunger_indicator.draw();
}

void
Gui::Graphic::PlayerInterface::zoom()
{
    float cell_length            = WorldCell::getLength();
    sf::Vector2f hero_shape_size = {
        cell_length * Gui::getInstance()->graphic.scope,
        cell_length * 1.8f * Gui::getInstance()->graphic.scope};

    sf::Vector2u window_size = Gui::getInstance()->m_window.getSize();

    sf::Vector2f wCentre = Gui::getInstance()->getWindowCentre();
    hero_shape.setPosition(wCentre.x - hero_shape_size.x * 0.5,
                           wCentre.y - hero_shape_size.y * 0.5);
    hero_shape.setSize(hero_shape_size);
}