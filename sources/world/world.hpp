#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>

#include <set>
#include <vector>

#include "dropped_object/dropped_object.hpp"

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

    void setDroppedObject(
        const std::vector<std::shared_ptr<DroppedObject>>& do_ptr_vec);
    void setDroppedObject(const std::shared_ptr<DroppedObject> do_ptr_vec);

    int getLength() const;

    Location& getLocation(int x, int y);
    Location& getLocation(const sf::Vector2f& coordinate);

    sf::Vector2i getCellPosition(const sf::Vector2f& point_coordinate) const;

    sf::Vector2f getCentreCoordinate() const;

    void saveToFile(std::ofstream& output_file);

    void loadFromFile(std::ifstream& input_file);

private:
    World();

    const int radius_updatable_locations;

    int m_length;

    LocationMatrix location_matrix;

    std::set<WorldCell*> updatable_cell_set;
};

#endif // WORLD_HPP