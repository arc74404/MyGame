#include "instrument.hpp"

#include "player/player.hpp"

const int Instrument::MAX_LEVEL = 2;

Instrument::Instrument(Type it, int level) : StorageObject(it), m_level(level)
{
}

int
Instrument::geLevel() const
{
    return m_level;
}

void
Instrument::use(const WorldCell& world_cell)
{
    PhysicalObject::Type obj_type = world_cell.getObjectPtr()->getType();

    float damage_power = 0;

    if (Player::getInstance()->isReadyToHit())
    {
        if (m_type == Type::AXE)
        {
            damage_power = standart_damage_power * (2 + m_level * 5);

            if (obj_type == PhysicalObject::Type::APPLE_TREE ||
                obj_type == PhysicalObject::Type::BIRCH_TREE)
            {
                world_cell.getObjectPtr()->damage(damage_power);
                Player::getInstance()->restartTimeRechargeAsSeconds(
                    standart_damage_power * 2);
            }
        }
        else if (m_type == Type::PICKAXE)
        {
            damage_power = standart_damage_power * (2 + m_level * 5);

            if (obj_type == PhysicalObject::Type::STONE)
            {
                world_cell.getObjectPtr()->damage(damage_power);
                Player::getInstance()->restartTimeRechargeAsSeconds(
                    standart_damage_power * 2);
            }
        }
    }
}

StorageObject::GeneralType
Instrument::getGeneralType() const
{
    return GeneralType::INSTRUMENT;
}

std::shared_ptr<StorageObject>
Instrument::getCopyObject() const
{
    return std::make_shared<Instrument>(Instrument(this->m_type, m_level));
}