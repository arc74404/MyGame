#include "dropped_resource.hpp"

DroppedResource::DroppedResource(StorageObject::Type tt) : DroppedObject(tt)
{
}

StorageObject::GeneralType
DroppedResource::getGeneralType() const
{
    return StorageObject::GeneralType::RESOURCE;
}