#include "grass.hpp"

const int Grass::MAX_LENGTH = 6;

Grass::Grass()
    : PhysicalObject(PhysicalObject::Type::GRASS, {1, 1}, -1), length(0)
{
    picture_shift = {0, 0};
    picture_size  = {1, 1};
}

void
Grass::update()
{
}

int
Grass::getPictureIndex() const
{
    return 0;
}

bool
Grass::isObstructive() const
{
    return false;
}
