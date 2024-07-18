#include "player.hpp"

#include <iostream>

#include "app/app.hpp"
#include "gui/gui.hpp"
#include "storage/instrument.hpp"
#include "world/cell.hpp"
#include "world/location.hpp"
#include "world/world.hpp"

Player::Player() : m_status(Status::STAND), hunger(100), health(100)
{
    movement_data.m_position = World::getInstance()->getCentreCoordinate();

    movement_data.speed = 40;

    collision_data.base_length = WorldCell::getLength() * 0.5;
    collision_data.base_width  = WorldCell::getLength() * 0.1;

    movement_data.m_flank = Flank::RIGHT;

    inventory.resize(40);
    hand_vector.resize(5);

    for (int i = 0; i < inventory.size(); ++i)
    {
        inventory[i].setObject(std::make_shared<StorageObject>(
            StorageObject(StorageObject::Type::HAND)));
    }
    for (int i = 0; i < hand_vector.size(); ++i)
    {
        StorageObjectPtr st_obj_ptr = std::make_shared<StorageObject>(
            StorageObject(StorageObject::Type::HAND));

        hand_vector[i].setObject(st_obj_ptr);
    }
    StorageObjectPtr st_obj_ptr = std::make_shared<Instrument>(
        Instrument(Instrument::InstrumentType::PICKAXE, 0));

    hand_vector[0].setObject(st_obj_ptr);

    st_obj_ptr = std::make_shared<Instrument>(
        Instrument(Instrument::InstrumentType::PICKAXE, 2));

    hand_vector[1].setObject(st_obj_ptr);

    clock_recharge.restart();
}

Player*
Player::getInstance()
{
    static Player inst;
    return &inst;
}

void
setRect(sf::Vector2f vector_array[], sf::Vector2f position, sf::Vector2f size)
{
    vector_array[0] = position;
    vector_array[1] = {position.x + size.x, position.y};
    vector_array[2] = {position.x + size.x, position.y + size.y};
    vector_array[3] = {position.x, position.y + size.y};
    vector_array[4] = vector_array[0];
}

sf::Vector2f
segments_cross(sf::Vector2f a[], sf::Vector2f b[])
{
    sf::Vector2f dot;

    const sf::Vector2f NULL_VECTOR = {0, 0};

    float n;

    if (a[1].y - a[0].y != 0)
    {
        float q  = (a[1].x - a[0].x) / (a[0].y - a[1].y);
        float sn = (b[0].x - b[1].x) + (b[0].y - b[1].y) * q;
        if (!sn)
        {
            return NULL_VECTOR;
        }
        float fn = (b[0].x - a[0].x) + (b[0].y - a[0].y) * q;
        n        = fn / sn;
    }
    else
    {
        if (!(b[0].y - b[1].y))
        {
            return NULL_VECTOR;
        }
        n = (b[0].y - a[0].y) / (b[0].y - b[1].y);
    }

    dot.x = b[0].x + (b[1].x - b[0].x) * n;
    dot.y = b[0].y + (b[1].y - b[0].y) * n;

    ////////////////////// находим точку пересечения прямых

    if (!((((dot.x >= a[0].x && dot.x <= a[1].x) ||

            (dot.x <= a[0].x && dot.x >= a[1].x)) &&

           ((dot.y >= a[0].y && dot.y <= a[1].y) ||
            (dot.y <= a[0].y && dot.y >= a[1].y))) &&

          (((dot.x >= b[0].x && dot.x <= b[1].x) ||

            (dot.x <= b[0].x && dot.x >= b[1].x)) &&

           ((dot.y >= b[0].y && dot.y <= b[1].y) ||

            (dot.y <= b[0].y && dot.y >= b[1].y)))))
    {
        dot = NULL_VECTOR;
    }

    return dot;
}

void
Player::restartTimeRechargeAsSeconds(float tt)
{
    clock_recharge.restart();
    time_recharge_seconds = tt;
}

bool
Player::isReadyToHit()
{
    return clock_recharge.getElapsedTime().asSeconds() >= time_recharge_seconds;
}

void
Player::align(sf::IntRect int_rect)
{
    sf::Vector2f a[5];
    sf::Vector2f left_up_player_collision;

    setRect(a,
            {movement_data.m_position.x - collision_data.base_length * 0.5f,
             movement_data.m_position.y - collision_data.base_width},
            {collision_data.base_length, collision_data.base_width});

    sf::Vector2f b[5];

    setRect(b,
            {float(int_rect.getPosition().x), float(int_rect.getPosition().y)},
            {float(int_rect.getSize().x), float(int_rect.getSize().y)});

    b[4] = b[0];

    float penetration_x = 100000;
    float penetration_y = 100000;

    bool is_intersect = false;

    ////////////////////////////
    for (int i = 0; i < 4; i += 2)
    {
        sf::Vector2f aa[] = {sf::Vector2f(a[i]), sf::Vector2f(a[i + 1])};

        for (int j = 1; j < 4; j += 2)
        {
            sf::Vector2f bb[] = {sf::Vector2f(b[j]), sf::Vector2f(b[j + 1])};

            sf::Vector2f dot = segments_cross(aa, bb);

            if (!(dot.x == 0 && dot.y == 0))
            {
                if (a[1].x > b[1].x)
                {
                    penetration_x = dot.x - a[0].x;
                }
                else
                {
                    penetration_x = dot.x - a[1].x;
                }
                is_intersect = true;
            }
        }
    }
    //////////////////////////////
    for (int i = 1; i < 4; i += 2)
    {
        sf::Vector2f aa[] = {sf::Vector2f(a[i]), sf::Vector2f(a[i + 1])};

        for (int j = 0; j < 4; j += 2)
        {
            sf::Vector2f bb[] = {sf::Vector2f(b[j]), sf::Vector2f(b[j + 1])};

            sf::Vector2f dot = segments_cross(aa, bb);

            if (!(dot.x == 0 && dot.y == 0))
            {
                if (a[0].y > b[0].y)
                {
                    penetration_y = dot.y - a[0].y;
                }
                else
                {
                    penetration_y = dot.y - a[3].y;
                }
                is_intersect = true;
            }
        }
    }

    static int _count = 0;

    if (is_intersect)
    {
        if (abs(penetration_x) < abs(penetration_y))
        {
            movement_data.m_position.x += penetration_x;
            // std::cout << "X:\n";
            // std::cout << "x: " << penetration_x << '\n';
            // std::cout << "y: " << penetration_y << '\n';
            // std::cout << "----------------------------------------\n";
        }
        else
        {
            movement_data.m_position.y += penetration_y;
            // std::cout << "Y:\n";
            // std::cout << "x: " << penetration_x << '\n';
            // std::cout << "y: " << penetration_y << '\n';
            // std::cout << "----------------------------------------\n";
        }
    }
}

void
Player::handleCollision()
{
    sf::Vector2i cell_position;
    float penetration_x, penetration_y;

    int location_length = Location::getLength();
    int cell_length     = WorldCell::getLength();

    sf::Vector2i location_position;

    sf::Vector2f extreme_point_coordinate;

    bool need_align = false;

    cell_position =
        World::getInstance()->getCellPosition(movement_data.m_position);
    location_position = {cell_position.x / location_length,
                         cell_position.y / location_length};

    ///////////////////////////////////////////////////////////////// LEFT UP
    extreme_point_coordinate = {
        movement_data.m_position.x - collision_data.base_length * 0.5f,
        movement_data.m_position.y - collision_data.base_width};

    cell_position =
        World::getInstance()->getCellPosition(extreme_point_coordinate);
    location_position = {cell_position.x / location_length,
                         cell_position.y / location_length};

    if (World::getInstance()
            ->getLocation(location_position.x, location_position.y)
            .getCell(cell_position.x % location_length,
                     cell_position.y % location_length)
            .isObstructive())
    {
        sf::Vector2i lu_coordinate(cell_position.x * cell_length,
                                   cell_position.y * cell_length);

        sf::IntRect r(lu_coordinate, {cell_length, cell_length});
        align(r);
        need_align = true;
    }

    /////////////////////////////////////////////////////////////////// LEFT
    /// DOWN
    extreme_point_coordinate = {movement_data.m_position.x -
                                    collision_data.base_length * 0.5f,
                                movement_data.m_position.y};

    cell_position =
        World::getInstance()->getCellPosition(extreme_point_coordinate);
    location_position = {cell_position.x / location_length,
                         cell_position.y / location_length};

    if (World::getInstance()
            ->getLocation(location_position.x, location_position.y)
            .getCell(cell_position.x % location_length,
                     cell_position.y % location_length)
            .isObstructive())
    {
        sf::Vector2i lu_coordinate(cell_position.x * cell_length,
                                   cell_position.y * cell_length);

        sf::IntRect r(lu_coordinate, {cell_length, cell_length});
        align(r);
        need_align = true;
    }

    /////////////////////////////////////////////////////////////////// RIGHT
    /// DOWN
    extreme_point_coordinate = {movement_data.m_position.x +
                                    collision_data.base_length * 0.5f,
                                movement_data.m_position.y};

    cell_position =
        World::getInstance()->getCellPosition(extreme_point_coordinate);
    location_position = {cell_position.x / location_length,
                         cell_position.y / location_length};

    if (World::getInstance()
            ->getLocation(location_position.x, location_position.y)
            .getCell(cell_position.x % location_length,
                     cell_position.y % location_length)
            .isObstructive())
    {
        sf::Vector2i lu_coordinate(cell_position.x * cell_length,
                                   cell_position.y * cell_length);

        sf::IntRect r(lu_coordinate, {cell_length, cell_length});
        align(r);
        need_align = true;
    }
    /////////////////////////////////////////////////////////////////// RIGHT UP
    extreme_point_coordinate = {
        movement_data.m_position.x + collision_data.base_length * 0.5f,
        movement_data.m_position.y - collision_data.base_width};

    cell_position =
        World::getInstance()->getCellPosition(extreme_point_coordinate);
    location_position = {cell_position.x / location_length,
                         cell_position.y / location_length};

    if (World::getInstance()
            ->getLocation(location_position.x, location_position.y)
            .getCell(cell_position.x % location_length,
                     cell_position.y % location_length)
            .isObstructive())
    {
        sf::Vector2i lu_coordinate(cell_position.x * cell_length,
                                   cell_position.y * cell_length);

        sf::IntRect r(lu_coordinate, {cell_length, cell_length});
        align(r);
        need_align = true;
    }
    // return need_align;
}

void
Player::walk()
{
    float radius = 1.8;

    sf::Vector2f m = movement_data.next_position - movement_data.m_position;

    sf::Vector2f direction;

    if (m.x == 0)
    {
        direction.x = 0.001;
    }
    else
    {
        direction.x = 1 / sqrt((m.y * m.y) / (m.x * m.x) + 1);
        direction.y = m.y / m.x * direction.x;
    }

    if (m.x < 0)
    {
        direction.x *= -1;
        direction.y *= -1;

        movement_data.m_flank = Flank::LEFT;
    }
    else movement_data.m_flank = Flank::RIGHT;

    movement_data.m_position += direction *
                                App::getInstance()->getCycleTime().asSeconds() *
                                movement_data.speed;

    if (std::pow(movement_data.m_position.x - movement_data.next_position.x,
                 2) +
            std::pow(movement_data.m_position.y - movement_data.next_position.y,
                     2) <=
        radius)
    {
        movement_data.m_position = movement_data.next_position;

        m_status = Status::STAND;
    }
    handleCollision();
}

void
Player::die()
{
}

void
Player::moveNextPosition(const sf::Vector2f& m)
{
    if (abs(m.x) < 3 && abs(m.y) < 3) return;
    movement_data.next_position = movement_data.m_position + m;

    m_status = Status::WALK;
}

void
Player::update()
{
    float cycle_time = App::getInstance()->getCycleTime().asSeconds();

    if (m_status == Status::WALK)
    {
        walk();
    }

    /////////////////////////////////
    hunger -= (cycle_time);

    if (hunger >= 100)
    {
        hunger = 100;
    }
    ////////////////////////////////
    if (m_status == Status::WALK) movement_data.walk_time_seconds += cycle_time;
    else movement_data.walk_time_seconds = 0;
    /////////////////////////////////

    if (hunger <= 0)
    {
        die();
    }
}

void
Player::operate(const WorldCell& world_cell, const StorageCell& using_hand)
{
    using_hand.getObject()->use(world_cell);
}

void
Player::stopMoving()
{
    movement_data.next_position = movement_data.m_position;

    m_status = Status::STAND;
}

int
Player::getInventorySize()
{
    return inventory.size();
}
int
Player::getHandVectorSize()
{
    return hand_vector.size();
}

Player::Status
Player::getStatus()
{
    return m_status;
}

sf::Vector2f
Player::getPosition()
{
    return movement_data.m_position;
}

float
Player::getWalkTimeSeconds()
{
    return movement_data.walk_time_seconds;
}

float
Player::getProcentHealth()
{
    return health / MAX_HEALTH;
}

float
Player::getProcentHunger()
{
    return hunger / MAX_HUNGER;
}

StorageCell&
Player::getInventoryCell(int index)
{
    return inventory[index];
}

StorageCell&
Player::getHandCell(int index)
{
    static StorageCell extra_empty_cell;
    extra_empty_cell.setObject(std::make_shared<StorageObject>(
                                   StorageObject(StorageObject::Type::HAND)),
                               1);
    if (index < 0 || index >= hand_vector.size())
    {
        return extra_empty_cell;
    }
    return hand_vector[index];
}

Player::Flank
Player::getFlank()
{
    return movement_data.m_flank;
}

float
Player::getLeftRechargeTimeAsSeconds()
{
    return time_recharge_seconds - clock_recharge.getElapsedTime().asSeconds();
}

float
Player::getFullRechargeTimeAsSeconds()
{
    return time_recharge_seconds;
}