#include "dropped_resource.hpp"

DroppedResource::DroppedResource(StorageObject::Type tt, int c,
                                 const sf::Vector2f& pos)
    : DroppedObject(tt, c, pos)
{
}

StorageObject::GeneralType
DroppedResource::getGeneralType() const
{
    return StorageObject::GeneralType::RESOURCE;
}