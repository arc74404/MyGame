#ifndef STORAGE_OBJECT_HPP
#define STORAGE_OBJECT_HPP
#include "world/cell.hpp"

class StorageObject
{
public:
    enum class Type
    {
        HAND    = 0,
        PICKAXE = 1,
        AXE,
        WOOD,
        STONE,
        STRAWBERRY,
        BLUEBERRY,
        APPLE
    };

    enum class GeneralType
    {
        HAND       = 0,
        INSTRUMENT = 1,
        RESOURCE
    };

    StorageObject(Type t);

    Type getType() const;

    virtual std::shared_ptr<StorageObject> getCopyObject() const;

    virtual GeneralType getGeneralType() const;

    virtual void use(const WorldCell& world_cell);

    virtual bool operator==(const StorageObject& other);

protected:
    Type m_type;

    static const float standart_time_recharge_seconds;

    static const float standart_damage_power;
};

#endif // !STORAGE_OBJECT_HPP