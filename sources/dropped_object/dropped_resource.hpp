#ifndef DROPPED_RESOURCE_HPP
#define DROPPED_RESOURCE_HPP

#include "dropped_object/dropped_object.hpp"
#include "storage/resource.hpp"

class DroppedResource : public DroppedObject
{
public:
    DroppedResource(StorageObject::Type tt, int c,
                    const sf::Vector2f& pos);

    StorageObject::GeneralType getGeneralType() const override;

private:
};

#endif //! DROPPED_RESOURCE_HPP