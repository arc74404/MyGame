#ifndef CIRCLE_BUTTON_HPP
#define CIRCLE_BUTTON_HPP

#include "base_button.hpp"

class CircleButton : public BaseButton
{
public:
    CircleButton();

    bool isPointInButton(const sf::Vector2f& point) const override;

    void setDiameter(float size);

    float getDiameter() const;

private:
    sf::Vector2f centre_position;

    float m_diameter;
    float m_radius;
};

#endif // !CIRCLE_BUTTON_HPP