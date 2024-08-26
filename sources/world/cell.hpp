#ifndef CELL_HPP
#define CELL_HPP

#include <shared_mutex>

#include "physical_object/physical_object.hpp"

typedef std::shared_ptr<PhysicalObject> PhysicalObjectPtr;

class WorldCell
{
public:
    static int getLength();

    WorldCell();

    WorldCell(const WorldCell& other);

    void setPhysicalObjectPtr(const PhysicalObjectPtr physical_object_ptr,
                              bool main, const sf::Vector2f& pos);

    PhysicalObjectPtr getObjectPtr() const;

    bool isMain() const;
    bool isEmpty() const;
    bool isObstructive() const;

    sf::Vector2f getPosition();

    void operator=(const WorldCell&);

    bool operator<(const WorldCell&) const;

private:
    static int m_length;

    sf::Vector2f m_position;

    bool is_main;

    PhysicalObjectPtr object_ptr;
};

#endif // CELL_HPP