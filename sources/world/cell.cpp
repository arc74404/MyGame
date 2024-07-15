#include "cell.hpp"

int WorldCell::m_length = 20;

WorldCell::WorldCell() : is_main(false)
{
}

void
WorldCell::setPhysicalObjectPtr(const PhysicalObjectPtr physical_object_ptr,
                           bool main)
{
    object_ptr = physical_object_ptr;

    is_main = main;
}

int
WorldCell::getLength()
{
    return m_length;
}

PhysicalObjectPtr
WorldCell::getObjectPtr() const
{
    return object_ptr;
}

bool
WorldCell::isMain() const
{
    return is_main;
}

bool
WorldCell::isEmpty() const
{
    return object_ptr == NULL;
}

bool
WorldCell::operator<(const WorldCell& other) const
{
    return this->object_ptr < other.object_ptr;
}

bool
WorldCell::isObstructive() const
{
    return object_ptr->isObstructive();
}