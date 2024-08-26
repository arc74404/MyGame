#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "storage/storage_object.hpp"

class Instrument : public StorageObject
{
public:
    Instrument(Type it, int level);

    int geLevel() const;

    GeneralType getGeneralType() const override;

    void use(const WorldCell& world_cell) override;

    std::shared_ptr<StorageObject> getCopyObject() const override;

    static const int MAX_LEVEL;

private:
    // static float

    int m_level;
};

#endif // !INSTRUMENT_HPP
