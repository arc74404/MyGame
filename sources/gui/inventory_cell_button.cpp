#include "inventory_cell_button.hpp"

#include <iostream>

#include "gui.hpp"
#include "is_key_button_clicked_off.hpp"

InventoryCellButton::InventoryCellButton() : RectangleButton()
{
}

const std::vector<sf::RectangleShape>&
InventoryCellButton::getObjectCountShapeVectorRef()
{
    return object_count_shape_vector;
}

void
InventoryCellButton::update()
{
    sf::Vector2f mouse_position = Gui::getInstance()->getMousePosition();
    bool is_button_pressed      = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isPointInButton(mouse_position))
    {
        if (is_button_pressed)
        {
            if (status != BaseButton::Status::NOT_SHINE)
            {
                status = BaseButton::Status::SHINE;
            }
        }
        else
        {
            status = BaseButton::Status::HIGHLIGHTED;
        }
    }
    else
    {
        if (status != BaseButton::Status::SHINE || !is_button_pressed)
        {
            status = BaseButton::Status::NOT_SHINE;
        }
    }
}
const sf::RectangleShape&
InventoryCellButton::getInventoryObjectShapeRef()
{
    return inventory_object_shape;
}

void
InventoryCellButton::setCount(int count)
{
    std::string str_count = std::to_string(count);

    object_count_shape_vector.resize(str_count.size());

    for (int i = 0; i < object_count_shape_vector.size(); ++i)
    {
        object_count_shape_vector[i].setTexture(
            Gui::getInstance()->graphic.getCharTexturePtr());
    }

    try
    {
        if (count < 0 || count >= 100)
        {
            throw std::exception("Count shoud be in diaposon [0;99]");
        }

        for (int i = 0; i < str_count.size(); ++i)
        {
            object_count_shape_vector[i].setTextureRect(
                Gui::getInstance()->graphic.getCharTextureRect(str_count[i]));
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    setSize(getSize());
}

void
InventoryCellButton::setInventoryObjectTexture(const sf::Texture* texture)
{
    inventory_object_shape.setTexture(texture);
}

void
InventoryCellButton::setInventoryObjectTextureRect(const sf::IntRect& rect)
{
    inventory_object_shape.setTextureRect(rect);
}

void
InventoryCellButton::setPosition(const sf::Vector2f& position)
{
    BaseButton::setPosition(position);
    inventory_object_shape.setPosition(position);

    for (int i = 0; i < object_count_shape_vector.size(); ++i)
    {
        object_count_shape_vector[i].setPosition(
            {position.x + object_count_shape_vector[i].getSize().x * i +
                 inventory_object_shape.getSize().x * 0.13f,
             position.y + inventory_object_shape.getSize().y * 0.13f});
    }
}

void
InventoryCellButton::setSize(const sf::Vector2f& size)
{
    RectangleButton::setSize(size);
    inventory_object_shape.setSize(size);

    for (int i = 0; i < object_count_shape_vector.size(); ++i)
    {
        object_count_shape_vector[i].setSize({size.x * 0.1f, size.y * 0.2f});
    }
    setPosition(getPosition());
}
/////////////////////////////////////////////////////////////
HandCellButton::HandCellButton()
{
}

void
HandCellButton::setCheckingKey(sf::Keyboard::Key k)
{
    is_key_clicked_off.setKey(k);
}

void
HandCellButton::update()
{
    if (is_key_clicked_off())
    {
        if (status == BaseButton::Status::NOT_SHINE)
        {
            status = BaseButton::Status::SHINE;
        }
        else
        {
            status = BaseButton::Status::NOT_SHINE;
        }
    }
}

void
HandCellButton::turnOff()
{
    status = BaseButton::Status::NOT_SHINE;
}