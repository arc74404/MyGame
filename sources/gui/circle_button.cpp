#include "circle_button.hpp"

CircleButton::CircleButton() : BaseButton(ShapeType::RECTANGLE)
{
}

bool
CircleButton::isPointInButton(const sf::Vector2f& point) const
{
    return (std::pow(point.x - shape.getPosition().x, 2) +
            std::pow(point.y - shape.getPosition().y, 2)) <=
           std::pow(m_radius, 2);
}

void
CircleButton::setDiameter(float diameter)
{
    m_diameter = diameter;

    m_radius = m_diameter * 0.5;

    centre_position = {shape.getPosition().x + m_radius,
                       shape.getPosition().y + m_radius};
}

float
CircleButton::getDiameter() const
{
    return m_diameter;
}