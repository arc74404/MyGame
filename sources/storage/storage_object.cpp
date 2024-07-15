#include "storage/storage_object.hpp"

#include <iostream>

#include "player/player.hpp"
#include "world/cell.hpp"

const float StorageObject::standart_time_recharge_seconds = 0.5;

const float StorageObject::standart_damage_power = 1.f;

StorageObject::StorageObject(Type t) : m_type(t)
{
}

StorageObject::Type
StorageObject::getType() const
{
    return m_type;
}

void
StorageObject::use(const WorldCell& world_cell)
{
    PhysicalObject::Type obj_type = world_cell.getObjectPtr()->getType();

    float t =
        Player::getInstance()->clock_recharge.getElapsedTime().asSeconds();

    // std::cout << t << '\n';

    if (t >= standart_time_recharge_seconds)
    {
        if (obj_type == PhysicalObject::Type::BUSH_BLUEBERRY ||
            obj_type == PhysicalObject::Type::BUSH_STRAWBERRY)
        {
            world_cell.getObjectPtr()->damage(standart_damage_power);

            Player::getInstance()->clock_recharge.restart();
        }
    }
}