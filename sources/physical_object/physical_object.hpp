#ifndef PHYSICAL_OBJECT_HPP
#define PHYSICAL_OBJECT_HPP

#include <SFML/Graphics.hpp>

class PhysicalObject
{
public:
    enum class Type
    {
        BUSH_BLUEBERRY  = 0,
        BUSH_STRAWBERRY = 1,
        STONE           = 2,
        GRASS           = 4,
        APPLE_TREE      = 5,
        BIRCH_TREE      = 6
    };

    PhysicalObject(Type t, sf::Vector2i s);

    PhysicalObject(Type t, sf::Vector2i s, float h);

    virtual void update() = 0;

    void damage(float tt);

    float getStrength();

    // virtual void destroy() = 0;

    // virtual bool isCorrrectInstrument(const StorageObject& st_obj) = 0;

    Type getType();

    sf::Vector2i getSize();

    sf::Vector2i getPictureShift();
    sf::Vector2i getPictureSize();

    virtual int getPictureIndex() const = 0;

    virtual bool isObstructive() const = 0;

protected:
    float strength;

    sf::Vector2i m_size;

    sf::Vector2i picture_shift;
    sf::Vector2i picture_size;

    Type m_type;

    sf::Clock update_clock;
};

#endif // PHYSICAL_OBJECT_HPP