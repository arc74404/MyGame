#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "storage/storage_object.hpp"

class Instrument : public StorageObject
{
public:
    enum class InstrumentType
    {
        PICKAXE = 0,
        AXE     = 1
    };

    Instrument(InstrumentType it, int level);

    InstrumentType getInstrumentType() const;

    int geLevel();

    void use(const WorldCell& world_cell) override;

private:

    // static float 

    InstrumentType instrument_type;

    int m_level;
};

#endif // !INSTRUMENT_HPP
