#include <iostream>

#include "storage/craft_menu.hpp"

#include "gui.hpp"
#include "texture_storage.hpp"

Gui::Graphic::CraftMenuInterface::CraftRowInterface::CraftRowInterface()
{
    ingredient_shape_vector.resize(
        CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS);

    result_object_button.setInventoryObjectTexture(
        TextureStorage::getInstance()->storage_objects_texture.getTexturePtr());

    result_object_button.setTexture(
        TextureStorage::getInstance()->inventory_cell_texture.getTexturePtr());
    result_object_button.setTextureRect(
        TextureStorage::getInstance()
            ->inventory_cell_texture[BaseButton::Status::NOT_SHINE][0]);

    for (int i = 0; i < CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS;
         ++i)
    {
        ingredient_shape_vector[i].setInventoryObjectTexture(
            TextureStorage::getInstance()
                ->storage_objects_texture.getTexturePtr());

        ingredient_shape_vector[i].setInventoryObjectTextureRect(
            sf::IntRect(0, 0, 0, 0));

        ingredient_shape_vector[i].setTexture(
            TextureStorage::getInstance()
                ->inventory_cell_texture.getTexturePtr());
        ingredient_shape_vector[i].setTextureRect(
            TextureStorage::getInstance()
                ->inventory_cell_texture[BaseButton::Status::NOT_SHINE][0]);
    }
    // std::cout << &result_object_button << '\n';
    is_result_object_button_clicked_off.setButton(&result_object_button);
    is_result_object_button_clicked_off.setMouseButtonChecking(sf::Mouse::Left);
}

void
Gui::Graphic::CraftMenuInterface::CraftRowInterface::setSize(
    const sf::Vector2f& size)
{
    m_size = size;

    pass = m_size.x * 0.1f;

    float cell_length =
        std::min((size.x - pass) /
                     (CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS + 1),
                 size.y);

    result_object_button.setSize({cell_length, cell_length});

    for (int i = 0; i < CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS;
         ++i)
    {
        ingredient_shape_vector[i].setSize({cell_length, cell_length});
    }
    setPosition(result_object_button.getPosition());
}

void
Gui::Graphic::CraftMenuInterface::CraftRowInterface::setPosition(
    const sf::Vector2f& position)
{
    result_object_button.setPosition(position);

    // float skip = m_size.x - result_object_button.get
    float cell_length = result_object_button.getSize().x;

    for (int i = 0; i < CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS;
         ++i)
    {
        // ingredient_shape_vector[i].setOutlineThickness(3);
        ingredient_shape_vector[i].setPosition(
            {position.x + pass + (i + 1) * cell_length, position.y});
    }
}

void
Gui::Graphic::CraftMenuInterface::CraftRowInterface::setRowIndex(int index)
{
    row_index = index;

    const CraftMenu& craft_menu = Player::getInstance()->getCraftMenu();

    const CraftMenu::CraftRow& craft_row = craft_menu.getCraftRow(index);

    int ing_count = craft_row.ingredient_vector.size();

    int level_index = 0;

    if (craft_row.result_object.getObject()->getGeneralType() ==
        StorageObject::GeneralType::INSTRUMENT)
    {
        level_index = std::reinterpret_pointer_cast<const Instrument>(
                          craft_row.result_object.getObject())
                          ->geLevel();
    }
    result_object_button.setInventoryObjectTextureRect(
        TextureStorage::getInstance()->storage_objects_texture
            [craft_row.result_object.getObject()->getType()][level_index]);

    result_object_button.setCount(craft_row.result_object.getCount());

    for (int i = 0; i < ing_count; ++i)
    {
        // std::cout << "row index\n";
        ingredient_shape_vector[i].setInventoryObjectTextureRect(
            TextureStorage::getInstance()->storage_objects_texture
                [craft_row.ingredient_vector[i].getObject()->getType()][0]);

        ingredient_shape_vector[i].setCount(
            craft_row.ingredient_vector[i].getCount());
    }
    for (int i = ing_count;
         i < CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS; ++i)
    {
        ingredient_shape_vector[i].setInventoryObjectTextureRect(
            sf::IntRect(0, 0, 0, 0));
    }
}

void
Gui::Graphic::CraftMenuInterface::CraftRowInterface::update()
{
    is_result_object_button_clicked_off.update();

    result_object_button.update();

    result_object_button.setTextureRect(
        TextureStorage::getInstance()
            ->inventory_cell_texture[result_object_button.getStatus()][0]);

    for (int i = 0; i < ingredient_shape_vector.size(); ++i)
    {
        ingredient_shape_vector[i].setTextureRect(
            TextureStorage::getInstance()
                ->inventory_cell_texture[ingredient_shape_vector[i].getStatus()]
                                        [0]);
    }
    // std::cout << "-------------------\n" << &result_object_button << "\n";
    if (is_result_object_button_clicked_off() && Player::getInstance()
                                                     ->getCraftMenu()
                                                     .getCraftRow(row_index)
                                                     .isAvailableForCraft())
    {
        Player::getInstance()->take(
            Player::getInstance()->getCraftMenu().getCraftRow(row_index));
    }
}

void
Gui::Graphic::CraftMenuInterface::CraftRowInterface::draw()
{
    result_object_button.draw();

    for (int i = 0; i < ingredient_shape_vector.size(); ++i)
    {
        // std::cout << ingredient_shape_vector.size() << '\n';
        // std::cout << ingredient_shape_vector[i].getTextureRect().left <<
        // // '\n';
        // std::cout << ingredient_shape_vector.size() << '\n';
        ingredient_shape_vector[i].draw();
    }
}

void
Gui::Graphic::CraftMenuInterface::CraftRowInterface::operator=(
    const CraftRowInterface& other)
{
    this->ingredient_shape_vector = other.ingredient_shape_vector;
    this->result_object_button    = other.result_object_button;

    this->row_index = other.row_index;
    this->m_size    = other.m_size;
    this->pass      = other.pass;
}
