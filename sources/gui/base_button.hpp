#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class BaseButton
{
public:
    enum class ShapeType
    {
        CIRCLE    = 0,
        RECTANGLE = 1
    };

    enum class Status
    {
        NOT_SHINE   = 0,
        HIGHLIGHTED = 1,
        SHINE       = 2
    };

    BaseButton(ShapeType type);

    virtual bool isPointInButton(const sf::Vector2f& cursor_position) const = 0;

    virtual sf::Vector2f getPosition() const;

    ShapeType getShapeType();

    Status getStatus() const;

    virtual void setPosition(const sf::Vector2f& percentage_position);

    virtual void setTexture(const sf::Texture* texture);

    virtual void setTextureRect(const sf::IntRect& int_rect);

    virtual void draw() const;

    void update();

protected:
    ShapeType shape_type;

    Status status;

    sf::RectangleShape shape;
};

#endif // BUTTON_HPP