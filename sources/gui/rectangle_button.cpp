#include "rectangle_button.hpp"

bool
isPointInRectangle(const sf::Vector2f& point, const sf::Vector2f& position,
                   const sf::Vector2f& size)
{
    bool in_x = (point.x > position.x) && (point.x < position.x + size.x);
    bool in_y = (point.y > position.y) && (point.y < position.y + size.y);

    return in_x && in_y;
}

RectangleButton::RectangleButton() : BaseButton(ShapeType::RECTANGLE)
{
    // shape.setOutlineThickness(3);
    // shape.setOutlineColor(sf::Color::Red);
}

bool
RectangleButton::isPointInButton(const sf::Vector2f& point) const
{
    return isPointInRectangle(point, shape.getPosition(), shape.getSize());
}

void
RectangleButton::setSize(const sf::Vector2f& size)
{
    shape.setSize(size);
    // shape.setOutlineThickness(3);
}

sf::Vector2f
RectangleButton::getSize()
{
    return shape.getSize();
}