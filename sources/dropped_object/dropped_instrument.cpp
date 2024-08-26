#include "dropped_instrument.hpp"

DroppedInstrument::DroppedInstrument(StorageObject::Type tt, int ll)
    : DroppedObject(tt)
{
    m_level = ll;
}

int
DroppedInstrument::geLevel()
{
    return m_level;
}

StorageObject::GeneralType
DroppedInstrument::getGeneralType() const
{
    return StorageObject::GeneralType::INSTRUMENT;
}