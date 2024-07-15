#ifndef RECTANGLE_BUTTON_HPP
#define RECTANGLE_BUTTON_HPP

#include "base_button.hpp"

class RectangleButton : public BaseButton
{
public:
    RectangleButton();

    bool isPointInButton(const sf::Vector2f& point) const override;

    void setSize(const sf::Vector2f& size);

    sf::Vector2f getSize();

private:
};

#endif // !RECTANGLE_BUTTON_HPP