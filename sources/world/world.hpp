#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>

#include <set>
#include <vector>

#include "cell.hpp"

// #include "location.hpp"
class Location;

typedef std::vector<std::vector<Location>> LocationMatrix;

class World
{
public:
    static World* getInstance();

    void generate();

    void update();

    void setSize(int l);

    bool setObject(const sf::Vector2i& obj_pos, PhysicalObjectPtr po_ptr);

    int getLength() const;

    const Location& getLocation(int x, int y) const;
    const Location& getLocation(const sf::Vector2f& coordinate) const;

    sf::Vector2i getCellPosition(const sf::Vector2f& point_coordinate) const;

    sf::Vector2f getCentreCoordinate() const;

private:
    World();

    const int radius_updatable_locations;

    int m_length;

    LocationMatrix location_matrix;

    std::set<WorldCell> updatable_cell_list;
};

#endif // WORLD_HPP