#ifndef STORAGE_OBJECT_HPP
#define STORAGE_OBJECT_HPP
#include "world/cell.hpp"

class StorageObject
{
public:
    enum class Type
    {
        HAND       = 0,
        INSTRUMENT = 1,
        BLOCK,
        RESOURCE
    };

    StorageObject(Type t);

    Type getType() const;

    virtual void use(const WorldCell& world_cell);

protected:
    Type m_type;

    static const float standart_time_recharge_seconds;

    static const float standart_damage_power;
};

#endif // !STORAGE_OBJECT_HPP