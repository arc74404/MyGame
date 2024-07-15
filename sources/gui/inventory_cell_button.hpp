#ifndef INVENTORY_CELL_BUTTON_HPP
#define INVENTORY_CELL_BUTTON_HPP

#include "is_key_button_clicked_off.hpp"
#include "rectangle_button.hpp"

class InventoryCellButton : public RectangleButton
{
public:
    InventoryCellButton();

    void update();

    void setPosition(const sf::Vector2f& position);

    void setSize(const sf::Vector2f& size);

    void setInventoryObjectTexture(const sf::Texture* texture);

    void setInventoryObjectTextureRect(const sf::IntRect& rect);

    const sf::RectangleShape& getInventoryObjectShapeRef();

    const std::vector<sf::RectangleShape>& getObjectCountShapeVectorRef();

    void setCount(int count);

protected:
    sf::RectangleShape inventory_object_shape;

    std::vector<sf::RectangleShape> object_count_shape_vector;
};

class HandCellButton : public InventoryCellButton
{
public:
    HandCellButton();

    void update();

    void setCheckingKey(sf::Keyboard::Key k);

    void turnOff();

private:
    isKeyboardButtonClickedOff is_key_clicked_off;
};

#endif // !INVENTORY_CELL_BUTTON_HPP