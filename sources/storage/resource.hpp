#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "storage/storage_object.hpp"

class Resource : public StorageObject
{
public:
    Resource(Type rt);

    GeneralType getGeneralType() const override;

    std::shared_ptr<StorageObject> getCopyObject() const override;



private:
};

#endif // !RESOURCE_HPP
