#ifndef DROPPED_OBJECT_HPP
#define DROPPED_OBJECT_HPP
#include <SFML/Graphics.hpp>

#include "storage/storage_object.hpp"

class DroppedObject
{
public:
    static void setLength(float l);

    static float getLength();

    // DroppedObject(StorageObject::Type tt);

    DroppedObject(StorageObject::Type tt, int count, const sf::Vector2f& pos);

    void setPosition(const sf::Vector2f& pos);

    void setCount(int c);

    sf::Vector2f getPosition() const;

    int getCount() const;

    StorageObject::Type getType() const;

    virtual StorageObject::GeneralType getGeneralType() const = 0;

protected:
    static float length;

    StorageObject::Type m_type;

    sf::Vector2f m_position;

    int m_count;
};

#endif //! DROPPED_OBJECT_HPP