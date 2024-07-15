#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include "storage/storage_object.hpp"

class Resource : public StorageObject
{
public:
    enum class ResourceType
    {
        WOOD = 0,
        STONE     = 1
    };

    Resource(ResourceType rt);

    ResourceType getResourceType();

private:
    ResourceType resource_type;
};

#endif // !INSTRUMENT_HPP
