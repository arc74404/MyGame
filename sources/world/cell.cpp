#include "cell.hpp"

#include <iostream>

#include "physical_object/const_object/grass.hpp"
int WorldCell::m_length = 20;

WorldCell::WorldCell() : is_main(false)
{
}

WorldCell::WorldCell(const WorldCell& other)
{
    operator=(other);
}

void
WorldCell::setPhysicalObjectPtr(const PhysicalObjectPtr physical_object_ptr,
                                bool main, const sf::Vector2f& pos)
{
    object_ptr = physical_object_ptr;

    is_main = main;

    m_position = pos;
}

sf::Vector2f
WorldCell::getPosition()
{
    return m_position;
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

void
WorldCell::operator=(const WorldCell& other)
{
    this->is_main = other.is_main;

    this->object_ptr = other.object_ptr;
}

bool
WorldCell::isObstructive() const
{
    return object_ptr->isObstructive();
}