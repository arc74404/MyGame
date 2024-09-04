#include "dropped_instrument.hpp"

DroppedInstrument::DroppedInstrument(StorageObject::Type tt, int ll,
                                     const sf::Vector2f& pos)
    : DroppedObject(tt, 1, pos)
{
    m_level = ll;
}

int
DroppedInstrument::getLevel()
{
    return m_level;
}

StorageObject::GeneralType
DroppedInstrument::getGeneralType() const
{
    return StorageObject::GeneralType::INSTRUMENT;
}