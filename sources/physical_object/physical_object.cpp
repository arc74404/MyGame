#include "physical_object.hpp"

#include <iostream>

#include "app/app.hpp"
#include "gui/gui.hpp"

PhysicalObject::PhysicalObject(Type t, sf::Vector2i s)
    : PhysicalObject(t, s, 100)
{
}

PhysicalObject::PhysicalObject(Type t, sf::Vector2i s, float h)
    : m_size(s), m_type(t), strength(h)
{
}

void
PhysicalObject::damage(float dd)
{
    strength -= dd;
    std::cout << strength << "\n";
}

PhysicalObject::Type
PhysicalObject::getType()
{
    return m_type;
}

sf::Vector2i
PhysicalObject::getSize()
{
    return m_size;
}

sf::Vector2i
PhysicalObject::getPictureShift()
{
    return picture_shift;
}

sf::Vector2i
PhysicalObject::getPictureSize()
{
    return picture_size;
}

float
PhysicalObject::getStrength()
{
    return strength;
}