#include "world.hpp"

#include <iostream>

#include "physical_object/changeable_object/apple_tree.hpp"
#include "physical_object/changeable_object/birch_tree.hpp"
#include "physical_object/changeable_object/bush.hpp"
#include "physical_object/const_object/grass.hpp"
#include "physical_object/const_object/stone.hpp"
#include "player/player.hpp"

#include "location.hpp"
void
addUniqueCellsInSet(std::set<WorldCell>& objptr_set, Location& loc)
{
    int length = Location::getLength();
    for (int x = 0; x < length; ++x)
    {
        for (int y = 0; y < length; ++y)
        {
            if (loc.cell_matrix[x][y].getObjectPtr() != NULL)
            {
                objptr_set.insert(loc.cell_matrix[x][y]);
            }
        }
    }
}

World::World() : radius_updatable_locations(3)
{
}

World*
World::getInstance()
{
    static World w;
    return &w;
}

void
World::generate()
{
    int loc_size = Location::getLength();

    for (int x = 0; x < loc_size * m_length; ++x)
    {
        for (int y = 0; y < loc_size * m_length; ++y)
        {
            PhysicalObjectPtr p;
            int a = rand() % 100;
            // std::cout << x << " " << y << '\n';

            if (x / loc_size == m_length / 2 && y / loc_size == m_length / 2)
            {
                p = std::make_shared<Grass>(Grass());
            }
            else
            {
                if (a <= 10 && x < loc_size * m_length - 1 &&
                    y < loc_size * m_length - 1)
                    p = std::make_shared<Stone>(Stone());

                else if (a <= 20)
                    if (rand() % 2)
                    {
                        p = std::make_shared<Bush>(
                            Bush(PhysicalObject::Type::BUSH_BLUEBERRY));
                        // p = std::make_shared<Bush>(
                        //     Bush(PhysicalObject::Type::BUSH_BLUEBERRY));
                    }
                    else
                        p = std::make_shared<Bush>(
                            Bush(PhysicalObject::Type::BUSH_STRAWBERRY));
                else if (a <= 30)
                {
                    if (rand() % 2)
                    {
                        p = std::make_shared<BirchTree>(BirchTree());
                    }
                    else p = std::make_shared<AppleTree>(AppleTree());
                }

                else p = std::make_shared<Grass>(Grass());
            }
            if (!setObject({x, y}, p))
            {
                p = std::make_shared<Grass>(Grass());
                setObject({x, y}, p);
            }
        }
    }
}

void
World::update()
{
    sf::Vector2f player_position = Player::getInstance()->getPosition();

    sf::Vector2i player_location_position = {
        getCellPosition(player_position).x / Location::getLength(),
        getCellPosition(player_position).y / Location::getLength()};

    updatable_cell_list.clear();

    for (int i = -radius_updatable_locations; i <= radius_updatable_locations;
         ++i)
    {
        if (player_location_position.x + i < 0 ||
            player_location_position.x + i >= m_length)
        {
            continue;
        }

        for (int j = -radius_updatable_locations;
             j <= radius_updatable_locations; ++j)
        {
            if (player_location_position.y + j < 0 ||
                player_location_position.y + j >= m_length)
            {
                continue;
            }

            addUniqueCellsInSet(
                updatable_cell_list,
                location_matrix[player_location_position.x + i]
                               [player_location_position.y + j]);
        }
    }

    for (std::set<WorldCell>::iterator it = updatable_cell_list.cbegin();
         it != updatable_cell_list.cend(); it++)
    {
        it->getObjectPtr()->update();
    }
}

void
World::setSize(int l)
{
    try
    {
        static bool is_first = true;
        if (l % 2 == 0)
        {
            throw std::exception("The size of the world should be odd");
        }
        if (!is_first)
        {
            throw std::exception("You can use this method only once");
        }

        if (is_first)
        {
            m_length = l;
            std::vector<Location> location_column(m_length, Location());
            location_matrix.resize(m_length, location_column);
            is_first = false;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

bool
World::setObject(const sf::Vector2i& obj_pos, PhysicalObjectPtr po_ptr)
{
    std::vector<std::pair<sf::Vector2i, sf::Vector2i>> cell_coordinate_array;

    int location_length   = Location::getLength();
    sf::Vector2i obj_size = po_ptr->getSize();

    cell_coordinate_array.reserve(obj_size.x * obj_size.y);

    for (int x = obj_pos.x; x < obj_pos.x + obj_size.x; ++x)
    {
        for (int y = obj_pos.y; y < obj_pos.y + obj_size.y; ++y)
        {
            if (!location_matrix[x / location_length][y / location_length]
                     .cell_matrix[x % location_length][y % location_length]
                     .isEmpty())
                return false;
            else
                cell_coordinate_array.emplace_back(std::make_pair(
                    sf::Vector2i(x / location_length, y / location_length),
                    sf::Vector2i(x % location_length, y % location_length)));
        }
    }
    location_matrix[cell_coordinate_array[0].first.x]
                   [cell_coordinate_array[0].first.y]
                       .cell_matrix[cell_coordinate_array[0].second.x]
                                   [cell_coordinate_array[0].second.y]
                       .setPhysicalObjectPtr(po_ptr, true);

    for (int i = 1; i < cell_coordinate_array.size(); ++i)
    {
        location_matrix[cell_coordinate_array[i].first.x]
                       [cell_coordinate_array[i].first.y]
                           .cell_matrix[cell_coordinate_array[i].second.x]
                                       [cell_coordinate_array[i].second.y]
                           .setPhysicalObjectPtr(po_ptr, false);
    }

    return true;
}

int
World::getLength() const
{
    return m_length;
}

const Location&
World::getLocation(int x, int y) const
{
    return location_matrix[x][y];
}

const Location&
World::getLocation(const sf::Vector2f& coordinate) const
{
    int loc_size = Location::getLength() * WorldCell::getLength();
    return getLocation(coordinate.x / loc_size, coordinate.y / loc_size);
}

sf::Vector2i
World::getCellPosition(const sf::Vector2f& point_coordinate) const
{
    sf::Vector2i cell_position;
    cell_position.x = point_coordinate.x / WorldCell::getLength();
    cell_position.y = point_coordinate.y / WorldCell::getLength();
    return cell_position;
}

sf::Vector2f
World::getCentreCoordinate() const
{
    return {
        float(m_length * Location::getLength() * WorldCell::getLength() * 0.5),
        float(m_length * Location::getLength() * WorldCell::getLength() * 0.5)};
}
