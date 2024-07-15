#include "rectangle_button.hpp"

RectangleButton::RectangleButton() : BaseButton(ShapeType::RECTANGLE)
{
}

bool
RectangleButton::isPointInButton(const sf::Vector2f& point) const
{
    sf::Vector2f m_position = shape.getPosition();

    bool in_x = (point.x > m_position.x) &&
                (point.x < m_position.x + shape.getSize().x);
    bool in_y = (point.y > m_position.y) &&
                (point.y < m_position.y + shape.getSize().y);

    return in_x && in_y;
}

void
RectangleButton::setSize(const sf::Vector2f& size)
{
    shape.setSize(size);
}

sf::Vector2f
RectangleButton::getSize()
{
    return shape.getSize();
}