#include "location.hpp"

#include "physical_object/changeable_object/bush.hpp"
#include "physical_object/const_object/stone.hpp"
int Location::m_length = 0;

Location::Location()
{
    std::vector<WorldCell> cell_column(m_length, WorldCell());

    cell_matrix.resize(m_length, cell_column);
}

const WorldCell&
Location::getCell(int x, int y) const
{
    return cell_matrix[x][y];
}

const WorldCell&
Location::getCell(const sf::Vector2f& coordinate) const
{
    return getCell(coordinate.x / WorldCell::getLength(),
                   coordinate.y / WorldCell::getLength());
}

void
Location::setLength(int l)
{
    static bool is_first = true;

    if (is_first)
    {
        m_length = l;
    }
}

int
Location::getLength()
{
    return m_length;
}