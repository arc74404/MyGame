#include "stone.hpp"

#include "storage/instrument.hpp"
const int Stone::MAX_STRENGTH = 100;

Stone::Stone() : PhysicalObject(Type::STONE, {2, 2}, 20)
{
    picture_shift = {0, 0};
    picture_size  = {2, 2};
}

void
Stone::update()
{
}

int
Stone::getPictureIndex() const
{
    return 0;
}

bool
Stone::isObstructive() const
{
    return true;
}

bool
Stone::isCorrrectInstrument(const StorageObject& st_obj) const
{
    return st_obj.getType() == StorageObject::Type::PICKAXE;
}