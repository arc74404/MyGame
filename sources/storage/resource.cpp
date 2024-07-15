#include "resource.hpp"

Resource::Resource(ResourceType rt)
    : StorageObject(StorageObject::Type::RESOURCE), resource_type(rt)
{
}

Resource::ResourceType
Resource::getResourceType()
{
    return resource_type;
}