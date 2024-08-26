#include <iostream>

#include "gui.hpp"
#include "texture_storage.hpp"
void
Gui::Graphic::CraftMenuInterface::create()
{
    shift = 0;

    sf::Vector2f window_size = Gui::getInstance()->getWindowSize();
    sf::Vector2f b_size      = {window_size.x * 0.5f, window_size.y * 0.5f};
    sf::Vector2f b_pos       = {b_size.x, 0};

    background.setSize(b_size);

    background.setPosition(b_pos);

    background.setFillColor(sf::Color::Green);

    ///////////////////////////////////////////////////////////////////

    sf::Vector2f button_arrow_size = {b_size.x * 0.1f, b_size.y * 0.2f};

    up_arrow_button.setTexture(
        TextureStorage::getInstance()->arrow_button_texture.getTexturePtr());
    up_arrow_button.setSize(button_arrow_size);
    up_arrow_button.setTextureRect(
        TextureStorage::getInstance()
            ->arrow_button_texture[up_arrow_button.getStatus()][0]);

    up_arrow_button.setPosition({b_pos.x, b_pos.y});

    // //////////////////////////////////////////////////////////////////

    down_arrow_button.setTexture(
        TextureStorage::getInstance()->arrow_button_texture.getTexturePtr());

    down_arrow_button.setTextureRect(
        TextureStorage::getInstance()
            ->arrow_button_texture[up_arrow_button.getStatus()][1]);

    down_arrow_button.setSize(button_arrow_size);

    down_arrow_button.setPosition({b_pos.x, b_pos.y + button_arrow_size.y});

    //////////////////////////////////////////////////////////////////////

    sf::Vector2f cri_size = {b_size.x - button_arrow_size.x, b_size.y * 0.2f};
    craft_row_interface_vector.resize(5);

    for (int i = 0; i < craft_row_interface_vector.size(); ++i)
    {
        CraftRowInterface cri;

        cri.setPosition(
            {b_pos.x + button_arrow_size.x, b_pos.y + cri_size.y * i});

        cri.setSize(cri_size);

        cri.setRowIndex(i);

        // std::cout << cri.result_object_button.getTextureRect().left << '\n';
        // std::cout << craft_row_interface_vector[i]
        //                  .result_object_button.getTextureRect()
        //                  .left
        //           << '\n';

        craft_row_interface_vector[i] = cri;
    }
    close();
}

void
Gui::Graphic::CraftMenuInterface::draw()
{
    Gui::getInstance()->m_window.draw(background);

    for (int i = 0; i < craft_row_interface_vector.size(); ++i)
    {
        // std::cout << craft_row_interface_vector.size() << '\n';
        craft_row_interface_vector[i].draw();
    }
    up_arrow_button.draw();
    down_arrow_button.draw();
}

void
Gui::Graphic::CraftMenuInterface::raiseShift()
{
    if (shift >= Player::getInstance()->getCraftMenu().getRowCount() -
                     craft_row_interface_vector.size())
        return;
    shift += 1;
}

void
Gui::Graphic::CraftMenuInterface::lowerShift()
{
    if (shift == 0) return;
    shift -= 1;
}

void
Gui::Graphic::CraftMenuInterface::open()
{
    status = Status::OPEN;
}

void
Gui::Graphic::CraftMenuInterface::close()
{
    status = Status::CLOSE;
}

void
Gui::Graphic::CraftMenuInterface::updateRowInterfaceVector()
{

    for (int i = 0; i < craft_row_interface_vector.size(); ++i)
    {
        craft_row_interface_vector[i].update();
        craft_row_interface_vector[i].setRowIndex(i + shift);

        // std::cout << cri.result_object_button.getTextureRect().left <<
        // '\n'; std::cout << craft_row_interface_vector[i]
        //                  .result_object_button.getTextureRect()
        //                  .left
        //           << '\n';
    }
}

void
Gui::Graphic::CraftMenuInterface::update()
{
    static isDefaultButtonClickedOff is_up_arrow_button_clicked_off(
        &up_arrow_button, sf::Mouse::Left);

    static isDefaultButtonClickedOff is_down_arrow_button_clicked_off(
        &down_arrow_button, sf::Mouse::Left);

    is_up_arrow_button_clicked_off.update();
    is_down_arrow_button_clicked_off.update();

    static isKeyboardButtonClickedOff is_tab_clicked_off;
    is_tab_clicked_off.setKey(sf::Keyboard::Tab);
    is_tab_clicked_off.update();

    // if (int(Gui::getInstance()
    //             ->is_keyboard_button_clicked_off_map[sf::Keyboard::Tab]()))
    // {
    //     std::cout << 1 << '\n';
    // }

    if (status == Status::CLOSE)
    {
        if (is_tab_clicked_off())
        {
            open();
            return;
        }
    }
    else if (status == Status::OPEN)
    {
        if (is_tab_clicked_off())
        {
            close();
            return;
        }

        up_arrow_button.update();
        up_arrow_button.setTextureRect(
            TextureStorage::getInstance()
                ->arrow_button_texture[up_arrow_button.getStatus()][0]);

        down_arrow_button.update();
        down_arrow_button.setTextureRect(
            TextureStorage::getInstance()
                ->arrow_button_texture[down_arrow_button.getStatus()][1]);

        if (is_up_arrow_button_clicked_off())
        {
            lowerShift();
        }
        if (is_down_arrow_button_clicked_off())
        {
            raiseShift();
        }
        updateRowInterfaceVector();
    }
}

Gui::Graphic::CraftMenuInterface::Status
Gui::Graphic::CraftMenuInterface::getStatus()
{
    return status;
}