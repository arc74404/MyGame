#include "base_button.hpp"

#include "gui.hpp"

BaseButton::BaseButton(ShapeType t) : shape_type(t)
{
    status = BaseButton::Status::NOT_SHINE;
}

void
BaseButton::setPosition(const sf::Vector2f& position)
{
    shape.setPosition(position);
}

sf::Vector2f
BaseButton::getPosition() const
{
    return shape.getPosition();
}

void
BaseButton::setTexture(const sf::Texture* texture)
{
    shape.setTexture(texture);
}

void
BaseButton::setTextureRect(const sf::IntRect& int_rect)
{
    shape.setTextureRect(int_rect);
}

void
BaseButton::update()
{
    sf::Vector2f mouse_position = Gui::getInstance()->getMousePosition();
    bool is_button_pressed      = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isPointInButton(mouse_position))
    {
        if (is_button_pressed)
        {
            status = BaseButton::Status::SHINE;
        }
        else
        {
            status = BaseButton::Status::HIGHLIGHTED;
        }
    }
    else
    {

        status = BaseButton::Status::NOT_SHINE;
    }
}

void
BaseButton::draw() const
{
    Gui::getInstance()->m_window.draw(shape);
}

BaseButton::Status
BaseButton::getStatus() const
{
    return status;
}