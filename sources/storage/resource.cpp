#include "resource.hpp"

Resource::Resource(Type rt) : StorageObject(rt)
{
}

StorageObject::GeneralType
Resource::getGeneralType() const
{
    return GeneralType::RESOURCE;
}

std::shared_ptr<StorageObject>
Resource::getCopyObject() const
{
    return std::make_shared<Resource>(Resource(this->m_type));
}