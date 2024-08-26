#include <iostream>

#include "world/location.hpp"
#include "world/world.hpp"

#include "gui.hpp"
#include "texture_storage.hpp"

void
Gui::Graphic::PlayerInterface::create()
{

    hero_shape.setTexture(
        TextureStorage::getInstance()->hero_texture.getTexturePtr());

    health_indicator.create();
    hunger_indicator.create();
    recharge_hit_countdown.create();

    health_indicator.setDesignation("health");
    hunger_indicator.setDesignation("hunger");

    health_indicator.setColor(sf::Color::Red);
    hunger_indicator.setColor(sf::Color::Yellow);
    recharge_hit_countdown.setColor(sf::Color::Yellow);

    left_corner.setFillColor(sf::Color(255, 255, 255, 140));

    sf::Vector2u window_size = Gui::getInstance()->m_window.getSize();
    sf::Vector2f shape_size  = {window_size.x * 0.3f, window_size.y * 0.05f};
    sf::Vector2f shape_position1 = {window_size.y * 0.03f,
                                    window_size.y * 0.03f};
    health_indicator.setSize(shape_size);
    health_indicator.setPosition(shape_position1);

    sf::Vector2f shape_position2 = {shape_position1.x,
                                    shape_position1.y + shape_size.y +
                                        window_size.y * 0.05f};
    hunger_indicator.setSize(shape_size);
    hunger_indicator.setPosition(shape_position2);

    sf::Vector2f shape_position3 = {shape_position2.x,
                                    shape_position2.y + shape_size.y +
                                        window_size.y * 0.05f};
    recharge_hit_countdown.setSize(shape_size);
    recharge_hit_countdown.setPosition(shape_position3);

    sf::Vector2f left_corner_size = {
        shape_size.x, shape_position2.y + shape_size.y - shape_position1.y};

    left_corner.setSize(left_corner_size);
    left_corner.setPosition(shape_position1);

    work_radius_shape.setFillColor(sf::Color::Transparent);
    work_radius_shape.setOutlineThickness(3);
    work_radius_shape.setOutlineColor(sf::Color(123, 23, 88, 122));
    // work_radius_shape.setRadius(Player::getInstance()->getWorkRadius());
    // work_radius_shape.setPosition({Gui::getInstance()->getWindowCentre().x -
    //                                    Player::getInstance()->getWorkRadius(),
    //                                Gui::getInstance()->getWindowCentre().y -
    //                                    Player::getInstance()->getWorkRadius()});
}

void
Gui::Graphic::PlayerInterface::update()
{
    static isKeyboardButtonClickedOff is_E_clicked_off_map;
    is_E_clicked_off_map.setKey(sf::Keyboard::E);
    is_E_clicked_off_map.update();
    sf::Vector2f displacement_vector =
        Gui::getInstance()->getMousePosition() -
        Gui::getInstance()->graphic.getPlayerPositionInWindow();

    displacement_vector.x /= Gui::getInstance()->graphic.getScope();
    displacement_vector.y /= Gui::getInstance()->graphic.getScope();

    sf::Vector2f player_position = Player::getInstance()->getPosition();
    sf::Vector2f mouse_coordinate =
        Player::getInstance()->getPosition() + displacement_vector;

    Location& location = World::getInstance()->getLocation(mouse_coordinate);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Player::getInstance()->moveNextPosition(displacement_vector);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        // Player::getInstance()->stopMoving();
        const StorageCell& using_storage_cell =
            Gui::getInstance()
                ->graphic.inventory_interface.getUsingStorageCellRef();

        Player::getInstance()->operate(location, mouse_coordinate,
                                       using_storage_cell);
    }
    if (is_E_clicked_off_map())
    {
        Player::getInstance()->manipulate(location, mouse_coordinate);
    }
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
            r = TextureStorage::getInstance()->hero_texture[player_status][0];

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
                TextureStorage::getInstance()
                    ->hero_texture[Player::Status::WALK]
                    .size();

            r = TextureStorage::getInstance()
                    ->hero_texture[player_status][rect_index];

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
    int procent_health = Player::getInstance()->getProcentHealth() * 100;
    int procent_hunger = Player::getInstance()->getProcentHunger() * 100;

    health_indicator.setProcent(procent_health);
    hunger_indicator.setProcent(procent_hunger);

    Gui::getInstance()->m_window.draw(left_corner);

    health_indicator.draw();
    hunger_indicator.draw();

    if (!Player::getInstance()->isReadyToHit())
    {
        recharge_hit_countdown.setFullTime(
            Player::getInstance()->getFullRechargeTimeAsSeconds());
        recharge_hit_countdown.setSeconds(
            Player::getInstance()->getLeftRechargeTimeAsSeconds());
        recharge_hit_countdown.draw();
    }
    Gui::getInstance()->m_window.draw(work_radius_shape);
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

    work_radius_shape.setRadius(Player::getInstance()->getWorkRadius() *
                                Gui::getInstance()->graphic.scope);
    // work_radius_shape.setPosition({Gui::getInstance()->getWindowCentre().x -
    //                                    Player::getInstance()->getWorkRadius()
    //                                    * 2,
    //                                Gui::getInstance()->getWindowCentre().y -
    //                                    Player::getInstance()->getWorkRadius()
    //                                    * 2});
    sf::Vector2f radius_shape_position = {
        wCentre.x - work_radius_shape.getRadius(),
        wCentre.y - work_radius_shape.getRadius() +
            hero_shape.getSize().y * 0.5f};

    work_radius_shape.setPosition(radius_shape_position);
}