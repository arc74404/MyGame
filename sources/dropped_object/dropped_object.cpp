#include "dropped_object.hpp"

#include <iostream>

#include "world/cell.hpp"

#include "dropped_resource.hpp"

sf::Vector2f
getScatteredPosition(const sf::Vector2f& pos, float max_distance)
{
    sf::Vector2f new_pos = pos;

    int a = 1;

    if (rand() % 2)
    {
        a = -1;
    }

    new_pos.x += a * max_distance / (rand() % 6 + 1);
    new_pos.y += a * max_distance / (rand() % 6 + 1);

    return new_pos;
}

DroppedResource
createDroppedResource(StorageObject::Type type, const sf::Vector2f& pos,
                      int count)
{
    DroppedResource dr(type);

    dr.setPosition(pos);
    dr.setCount(count);

    return dr;
}

std::vector<std::shared_ptr<DroppedObject>>
getDroppedObjectPtrVector(const sf::Vector2f& pos, const PhysicalObjectPtr& obj)
{
    std::vector<std::shared_ptr<DroppedObject>> result_vec;

    PhysicalObject::Type ot = obj->getType();

    // std::cout << int(obj->getType()) << '\n';

    switch (ot)
    {
        case PhysicalObject::Type::STONE:
            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::STONE, pos, 3)));
            break;

        case PhysicalObject::Type::APPLE_TREE:
            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::WOOD, pos, 2)));

            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::APPLE, pos, 5)));

            break;

        case PhysicalObject::Type::BIRCH_TREE:
            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::WOOD, pos, 2)));

            break;

        case PhysicalObject::Type::BUSH_BLUEBERRY:
            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::WOOD, pos, 2)));
            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::BLUEBERRY, pos, 4)));
            break;

        case PhysicalObject::Type::BUSH_STRAWBERRY:
            result_vec.emplace_back(std::make_shared<DroppedResource>(
                createDroppedResource(StorageObject::Type::WOOD, pos, 2)));
            result_vec.emplace_back(
                std::make_shared<DroppedResource>(createDroppedResource(
                    StorageObject::Type::STRAWBERRY, pos, 4)));
            break;

        default:
            break;
    }

    return result_vec;
}

float DroppedObject::length;

void
DroppedObject::setLength(float l)
{
    length = l;
}

float
DroppedObject::getLength()
{
    return length;
}

DroppedObject::DroppedObject(StorageObject::Type tt)
{
    m_type = tt;
}

void
DroppedObject::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;
}

void
DroppedObject::setCount(int c)
{
    m_count = c;
}

sf::Vector2f
DroppedObject::getPosition() const
{
    return m_position;
}

int
DroppedObject::getCount() const
{
    return m_count;
}

StorageObject::Type
DroppedObject::getType() const
{
    return m_type;
}
