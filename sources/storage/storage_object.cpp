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

StorageObject::GeneralType
StorageObject::getGeneralType() const
{
    return GeneralType::HAND;
}

void
StorageObject::use(const WorldCell& world_cell)
{
    PhysicalObject::Type obj_type = world_cell.getObjectPtr()->getType();

    // std::cout << t << '\n';

    if (Player::getInstance()->isReadyToHit())
    {
        if (obj_type == PhysicalObject::Type::BUSH_BLUEBERRY ||
            obj_type == PhysicalObject::Type::BUSH_STRAWBERRY)
        {
            world_cell.getObjectPtr()->damage(standart_damage_power);

            Player::getInstance()->restartTimeRechargeAsSeconds(
                standart_time_recharge_seconds);
        }
    }
}

std::shared_ptr<StorageObject>
StorageObject::getCopyObject() const
{
    return std::make_shared<StorageObject>(StorageObject(Type::HAND));
}

bool
StorageObject::operator==(const StorageObject& other)
{
    return this->m_type == other.m_type;
}