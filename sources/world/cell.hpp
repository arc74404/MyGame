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

    void setPhysicalObjectPtr(const PhysicalObjectPtr physical_object_ptr,
                              bool main);

    PhysicalObjectPtr getObjectPtr() const;

    bool isMain() const;
    bool isEmpty() const;
    bool isObstructive() const;

    bool operator<(const WorldCell&) const;

private:
    static int m_length;

    bool is_main;

    PhysicalObjectPtr object_ptr;
};

#endif // CELL_HPP