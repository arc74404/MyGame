#include "instrument.hpp"

#include "player/player.hpp"
Instrument::Instrument(InstrumentType it, int level)
    : StorageObject(StorageObject::Type::INSTRUMENT), instrument_type(it),
      m_level(level)
{
}

Instrument::InstrumentType
Instrument::getInstrumentType() const
{
    return instrument_type;
}

int
Instrument::geLevel()
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
        if (instrument_type == InstrumentType::AXE)
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
        else if (instrument_type == InstrumentType::PICKAXE)
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