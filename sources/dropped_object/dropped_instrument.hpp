#ifndef DROPPED_INSTRUMENT_HPP
#define DROPPED_INSTRUMENT_HPP
#include <SFML/Graphics.hpp>

#include "storage/instrument.hpp"

#include "dropped_object.hpp"

class DroppedInstrument : public DroppedObject
{
public:
    DroppedInstrument(StorageObject::Type tt, int ll, const sf::Vector2f& pos);

    int getLevel();

    StorageObject::GeneralType getGeneralType() const override;

private:
    int m_level;
};

#endif //! DROPPED_INSTRUMENT_HPP