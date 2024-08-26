#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <set>
#include <shared_mutex>
#include <vector>

#include "dropped_object/dropped_object.hpp"
#include "world/world.hpp"

#include "cell.hpp"

typedef std::vector<std::vector<WorldCell>> CellMatrix;

class Location;

void
addUniqueCellsInSet(std::set<WorldCell*>& objptr_list, Location& loc);

class Location
{
    friend void World::generate();
    friend bool World::setObject(const sf::Vector2i& obj_pos,
                                 PhysicalObjectPtr po_ptr);

    friend void addUniqueCellsInSet(std::set<WorldCell*>& objptr_list,
                                    Location& loc);

public:
    static void setLength(int);

    static int getLength();

    Location();

    const std::vector<std::shared_ptr<DroppedObject>>& getDroppedObjectVector()
        const;

    void addDroppedObject(
        const std::shared_ptr<DroppedObject>& dropped_object_ptr);

    const WorldCell& getCell(int x, int y) const;
    const WorldCell& getCell(const sf::Vector2f& coordinate) const;

    void destroyDroppedObject(int index);

private:
    CellMatrix cell_matrix;

    std::vector<std::shared_ptr<DroppedObject>> dropped_object_vector;

    static int m_length; // в количесвте клеток
};

#endif // LOCATION_HPP