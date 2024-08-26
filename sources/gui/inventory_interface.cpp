#include <iostream>

#include "gui.hpp"
#include "math.h"
#include "texture_storage.hpp"

// void
// Gui::Graphic::InventoryInterface::loadTexture()
// {

// }
void
Gui::Graphic::InventoryInterface::create()
{
    is_tab_clicked_off_map.setKey(sf::Keyboard::Tab);
    is_right_clicked_off.setMouseButton(sf::Mouse::Right);
    is_left_clicked_off.setMouseButton(sf::Mouse::Left);
    shift = 0;

    sf::Vector2f window_size = Gui::getInstance()->getWindowSize();
    sf::Vector2f b_size      = {window_size.x * 0.5f, window_size.y};
    sf::Vector2f b_pos       = {0, 0};

    background.setSize(b_size);

    background.setPosition(b_pos);

    background.setFillColor(sf::Color::Green);

    ///////////////////////////////////////////////////////////////////

    // sf::Vector2f button_arrow_size = {b_size.x * 0.1f, b_size.y * 0.2f};

    // up_arrow_button.setTexture(up_down_button_texture.getTexturePtr());
    // up_arrow_button.setSize(button_arrow_size);
    // up_arrow_button.setTextureRect(
    //     up_down_button_texture[up_arrow_button.getStatus()][0]);
    // up_arrow_button.setPosition({b_pos.x, b_pos.y});

    // //////////////////////////////////////////////////////////////////
    // static sf::IntRect reverse_int_rect =
    //     up_down_button_texture[up_arrow_button.getStatus()][0];

    // reverse_int_rect.top += reverse_int_rect.height;
    // reverse_int_rect.height *= -1;
    // down_arrow_button.setTexture(up_down_button_texture.getTexturePtr());
    // down_arrow_button.setTextureRect(reverse_int_rect);
    // down_arrow_button.setSize(button_arrow_size);
    // down_arrow_button.setPosition({b_pos.x, b_pos.y + button_arrow_size.y});

    row_length = 8;
    count_rows = (Player::getInstance()->getInventorySize() + row_length - 1) /
                 row_length;

    // float cell_size = (b_size.x - button_arrow_size.x) / row_length;

    // sf::Vector2f first_cell_position = {up_arrow_button.getPosition().x +
    //                                         button_arrow_size.x,
    //                                     up_arrow_button.getPosition().y};

    float inv_cell_length = std::min((b_size.x) / row_length,
                                     (b_size.y * 0.95f) / (count_rows + 1));

    sf::Vector2f first_cell_position = {b_pos.x, b_pos.y};

    ////////////////////////////////////////////////////////////////////////
    inventory_cell_button_vector.resize(
        Player::getInstance()->getInventorySize());

    int index;

    float space_length =
        (b_size.x - (inv_cell_length * row_length)) / (row_length - 1);

    for (int i = 0; i < count_rows; ++i)
    {
        for (int j = 0;
             j < row_length &&
             i * row_length + j < inventory_cell_button_vector.size();
             ++j)
        {
            index = i * row_length + j;
            inventory_cell_button_vector[index].setPosition(
                {first_cell_position.x + j * inv_cell_length + space_length * j,
                 first_cell_position.y + i * inv_cell_length});

            inventory_cell_button_vector[index].setSize(
                {inv_cell_length, inv_cell_length});

            inventory_cell_button_vector[index].setCount(0);

            inventory_cell_button_vector[index].setTexture(
                TextureStorage::getInstance()
                    ->inventory_cell_texture.getTexturePtr());

            inventory_cell_button_vector[index].setInventoryObjectTexture(
                TextureStorage::getInstance()
                    ->storage_objects_texture.getTexturePtr());

            inventory_cell_button_vector[index].setTextureRect(
                TextureStorage::getInstance()
                    ->inventory_cell_texture[BaseButton::Status::NOT_SHINE][0]);

            inventory_cell_button_vector[index].setInventoryObjectTextureRect(
                {0, 0, 0, 0});
        }
    }

    hand_cell_button_vector.resize(Player::getInstance()->getHandVectorSize());

    float hand_cell_length =
        std::min(background.getSize().x / hand_cell_button_vector.size(),
                 inv_cell_length);

    space_length = (b_size.x - (hand_cell_length *
                                Player::getInstance()->getHandVectorSize())) /
                   (Player::getInstance()->getHandVectorSize() - 1);

    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        hand_cell_button_vector[i].setCheckingKey(
            sf::Keyboard::Key(int(sf::Keyboard::Num1) + i));

        hand_cell_button_vector[i].setCount(0);

        hand_cell_button_vector[i].setInventoryObjectTexture(
            TextureStorage::getInstance()
                ->storage_objects_texture.getTexturePtr());

        hand_cell_button_vector[i].setInventoryObjectTextureRect({0, 0, 0, 0});

        hand_cell_button_vector[i].setTexture(
            TextureStorage::getInstance()
                ->inventory_cell_texture.getTexturePtr());

        hand_cell_button_vector[i].setTextureRect(
            TextureStorage::getInstance()
                ->inventory_cell_texture[BaseButton::Status::NOT_SHINE][0]);
    }

    transfer_cell.inventory_cell_button.setSize(
        {inv_cell_length, inv_cell_length});

    transfer_cell.inventory_cell_button.setTexture(
        TextureStorage::getInstance()->inventory_cell_texture.getTexturePtr());

    transfer_cell.inventory_cell_button.setInventoryObjectTexture(
        TextureStorage::getInstance()->storage_objects_texture.getTexturePtr());

    transfer_cell.inventory_cell_button.setTextureRect(sf::IntRect(0, 0, 0, 0));

    transfer_cell.inventory_cell_button.setInventoryObjectTextureRect(
        {0, 0, 0, 0});

    close();
}

void
Gui::Graphic::InventoryInterface::raiseShift()
{
    if ((shift + count_rows - 1) * (row_length + 1) >
        Player::getInstance()->getInventorySize())
        return;
    shift++;
}

void
Gui::Graphic::InventoryInterface::lowerShift()
{
    if (shift == 0) return;
    shift--;
}

void
Gui::Graphic::InventoryInterface::open()
{
    status = Status::OPEN;

    float hand_cell_length =
        std::min(background.getSize().x / hand_cell_button_vector.size(),
                 inventory_cell_button_vector[0].getSize().x);

    float space_length =
        (background.getSize().x -
         (hand_cell_length * Player::getInstance()->getHandVectorSize())) /
        (Player::getInstance()->getHandVectorSize() - 1);

    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        hand_cell_button_vector[i].turnOff();
        hand_cell_button_vector[i].setSize(
            {hand_cell_length, hand_cell_length});

        hand_cell_button_vector[i].setPosition(
            {background.getPosition().x + hand_cell_length * i +
                 space_length * i,
             background.getSize().y + background.getPosition().y -
                 hand_cell_length});
    }
}

void
Gui::Graphic::InventoryInterface::close()
{
    float hand_cell_length = Gui::getInstance()->getWindowSize().x * 0.05;

    sf::Vector2f start_position = {
        (Gui::getInstance()->getWindowSize().x -
         hand_cell_length * Player::getInstance()->getHandVectorSize()) *
            0.5f,
        Gui::getInstance()->getWindowSize().y - hand_cell_length * 2};

    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        hand_cell_button_vector[i].turnOff();
        hand_cell_button_vector[i].setPosition(
            {start_position.x + hand_cell_length * i, start_position.y});
        hand_cell_button_vector[i].setSize(
            {hand_cell_length, hand_cell_length});
    }
    status = Status::CLOSE;
}

void
Gui::Graphic::InventoryInterface::updateStorageObjectTexture(
    const StorageCell& st_cell, InventoryCellButton& inv_cell_button)
{
    StorageObjectPtr objPtr = st_cell.getObject();

    sf::IntRect int_rect = {0, 0, 0, 0};

    if (objPtr->getType() != StorageObject::Type::HAND &&
        st_cell.getCount() != 0)
    {
        if (objPtr->getGeneralType() == StorageObject::GeneralType::INSTRUMENT)
        {
            std::shared_ptr<Instrument> instrumentPtr =
                std::static_pointer_cast<Instrument>(objPtr);

            int_rect = TextureStorage::getInstance()
                           ->storage_objects_texture[instrumentPtr->getType()]
                                                    [instrumentPtr->geLevel()];
        }
        if (objPtr->getGeneralType() == StorageObject::GeneralType::RESOURCE)
        {
            std::shared_ptr<Resource> resourcePtr =
                std::static_pointer_cast<Resource>(objPtr);

            inv_cell_button.setInventoryObjectTexture(
                TextureStorage::getInstance()
                    ->storage_objects_texture.getTexturePtr());

            int_rect = TextureStorage::getInstance()
                           ->storage_objects_texture[resourcePtr->getType()][0];
        }
    }

    inv_cell_button.setInventoryObjectTextureRect(int_rect);
}

void
Gui::Graphic::InventoryInterface::updateTransfer(
    int index, StorageCell& st_cell, TransferCell::StorageType storage_type)
{
    if (storage_type == TransferCell::StorageType::HAND)
    {
        if (is_left_clicked_off() &&
            hand_cell_button_vector[index].isPointInButton(
                Gui::getInstance()->getMousePosition()) &&
            transfer_cell.isClear())
        {
            std::cout << "setData HAND\n";
            transfer_cell.setData(TransferCell::StorageType::HAND, index,
                                  st_cell.getObject(), st_cell.getCount());
            st_cell.clear();
        }
        else if (is_left_clicked_off() && !transfer_cell.isClear())
        {
            if (hand_cell_button_vector[index].isPointInButton(
                    Gui::getInstance()->getMousePosition()))
            {
                if (st_cell.getObject()->getType() ==
                    transfer_cell.getObject()->getType())
                {
                    int remainder = transfer_cell.getCount() +
                                    st_cell.getCount() -
                                    StorageCell::getCountLimit();

                    if (remainder < 0)
                    {
                        // int transfer_cell_object_count =
                        //     transfer_cell.getCount();
                        st_cell = transfer_cell;

                        st_cell.setCount(StorageCell::getCountLimit() +
                                         remainder);
                        // std::cout
                        //     << StorageCell::getCountLimit() + remainder
                        //     << '\n';

                        transfer_cell.clear();
                    }
                }
                else
                {
                    StorageCell extra_st_cell = transfer_cell;
                    transfer_cell.setData(TransferCell::StorageType::HAND,
                                          index, st_cell.getObject(),
                                          st_cell.getCount());
                    st_cell = extra_st_cell;
                }

                // transfer_cell.clear();
            }
        }
        if (is_right_clicked_off())
        {
            int tr_data_index = transfer_cell.getIndex();
            if (transfer_cell.getStorageType() ==
                    TransferCell::StorageType::HAND &&
                transfer_cell.getIndex() == index &&
                (st_cell.getObject()->getType() ==
                     transfer_cell.getObject()->getType() ||
                 st_cell.getCount() == 0))
            {
                int cell_object_count          = st_cell.getCount();
                int transfer_cell_object_count = transfer_cell.getCount();

                st_cell = transfer_cell;
                // std::cout <<
                // int(transfer_cell.getObject()->getType()) <<
                // '\n';
                st_cell.setCount(cell_object_count +
                                 transfer_cell_object_count / 2);
                transfer_cell.setCount((transfer_cell_object_count + 1) / 2);
                transfer_cell.inventory_cell_button.setCount(
                    transfer_cell.getCount());
            }
        }
    }
    if (storage_type == TransferCell::StorageType::INVENTORY)
    {
        if (is_left_clicked_off() &&
            inventory_cell_button_vector[index].isPointInButton(
                Gui::getInstance()->getMousePosition()) &&
            transfer_cell.isClear())
        {
            std::cout << "setData INVENTORY\n";
            transfer_cell.setData(TransferCell::StorageType::INVENTORY, index,
                                  st_cell.getObject(), st_cell.getCount());
            st_cell.clear();
        }
        else if (is_left_clicked_off() && !transfer_cell.isClear())
        {
            if (inventory_cell_button_vector[index].isPointInButton(
                    Gui::getInstance()->getMousePosition()))
            {
                if (st_cell.getObject()->getType() ==
                    transfer_cell.getObject()->getType())
                {
                    int remainder = transfer_cell.getCount() +
                                    st_cell.getCount() -
                                    StorageCell::getCountLimit();

                    if (remainder < 0)
                    {
                        // int transfer_cell_object_count =
                        //     transfer_cell.getCount();
                        st_cell = transfer_cell;

                        st_cell.setCount(StorageCell::getCountLimit() +
                                         remainder);
                        // std::cout
                        //     << StorageCell::getCountLimit() + remainder
                        //     << '\n';

                        transfer_cell.clear();
                    }
                }
                else
                {
                    StorageCell extra_st_cell = transfer_cell;
                    transfer_cell.setData(TransferCell::StorageType::INVENTORY,
                                          index, st_cell.getObject(),
                                          st_cell.getCount());
                    st_cell = extra_st_cell;
                }

                // transfer_cell.clear();
            }
        }
        if (is_right_clicked_off())
        {
            int tr_data_index = transfer_cell.getIndex();
            if (transfer_cell.getStorageType() ==
                    TransferCell::StorageType::INVENTORY &&
                transfer_cell.getIndex() == index &&
                (st_cell.getObject()->getType() ==
                     transfer_cell.getObject()->getType() ||
                 st_cell.getCount() == 0))
            {
                int cell_object_count          = st_cell.getCount();
                int transfer_cell_object_count = transfer_cell.getCount();

                st_cell = transfer_cell;
                // std::cout <<
                // int(transfer_cell.getObject()->getType()) <<
                // '\n';
                st_cell.setCount(cell_object_count +
                                 transfer_cell_object_count / 2);
                transfer_cell.setCount((transfer_cell_object_count + 1) / 2);
                transfer_cell.inventory_cell_button.setCount(
                    transfer_cell.getCount());
            }
        }
    }
}

void
Gui::Graphic::InventoryInterface::update()
{
    is_tab_clicked_off_map.update();
    is_right_clicked_off.update();
    is_left_clicked_off.update();

    if (status == Status::CLOSE)
    {
        if (is_tab_clicked_off_map())
        {
            open();
            goto end;
        }
        if (index_using_hand != -1)
        {
            hand_cell_button_vector[index_using_hand].update();
            if (hand_cell_button_vector[index_using_hand].getStatus() !=
                BaseButton::Status::SHINE)
            {
                index_using_hand = -1;
            }
        }

        for (int i = 0; i < hand_cell_button_vector.size(); ++i)
        {
            hand_cell_button_vector[i].update();
            hand_cell_button_vector[i].setCount(
                Player::getInstance()->getHandCell(i).getCount());

            if (hand_cell_button_vector[i].getStatus() ==
                BaseButton::Status::SHINE)
            {
                if (i != index_using_hand && index_using_hand != -1)
                {
                    hand_cell_button_vector[index_using_hand].turnOff();
                }
                index_using_hand = i;
            }
        }

        for (int i = 0; i < hand_cell_button_vector.size(); ++i)
        {
            hand_cell_button_vector[i].setTextureRect(
                TextureStorage::getInstance()->inventory_cell_texture
                    [hand_cell_button_vector[i].getStatus()][0]);
            updateStorageObjectTexture(Player::getInstance()->getHandCell(i),
                                       hand_cell_button_vector[i]);
        }
    }
    else if (status == Status::OPEN)
    {
        // static const BaseButton* t1 = &up_arrow_button;
        // static const BaseButton* t2 = &down_arrow_button;
        // static isDefaultButtonClickedOff
        // is_up_arrow_button_clicked_off(t1); static
        // isDefaultButtonClickedOff is_down_arrow_button_clicked_off(t2);
        // if (is_up_arrow_button_clicked_off())
        // {
        //     lowerShift();
        // }
        // else if (is_down_arrow_button_clicked_off())
        // {
        //     raiseShift();
        // }
        if (is_tab_clicked_off_map())
        {
            close();
            goto end;
        }
        // up_arrow_button.update();
        // down_arrow_button.update();
        // up_arrow_button.setTextureRect(
        //     up_down_button_texture[up_arrow_button.getStatus()][0]);
        // sf::IntRect reverse_int_rect =
        //     up_down_button_texture[down_arrow_button.getStatus()][0];
        // reverse_int_rect.top += reverse_int_rect.height;
        // reverse_int_rect.height *= -1;
        // down_arrow_button.setTextureRect(reverse_int_rect);

        // static isDefaultButtonClickedOff
        // is_inventory_cell_button_clicked_off;
        for (int i = 0; i < inventory_cell_button_vector.size(); ++i)
        {
            inventory_cell_button_vector[i].update();
            inventory_cell_button_vector[i].setTextureRect(
                TextureStorage::getInstance()->inventory_cell_texture
                    [inventory_cell_button_vector[i].getStatus()][0]);

            inventory_cell_button_vector[i].setCount(
                Player::getInstance()->getInventoryCell(i).getCount());

            int index_inventory = shift * row_length + i;

            if (index_inventory >= Player::getInstance()->getInventorySize())
                break;

            StorageCell& st_cell =
                Player::getInstance()->getInventoryCell(index_inventory);

            updateTransfer(i, st_cell, TransferCell::StorageType::INVENTORY);
            updateStorageObjectTexture(st_cell,
                                       inventory_cell_button_vector[i]);
        }

        for (int i = 0; i < hand_cell_button_vector.size(); ++i)
        {
            static_cast<InventoryCellButton*>(&hand_cell_button_vector[i])
                ->update();

            hand_cell_button_vector[i].setTextureRect(
                TextureStorage::getInstance()->inventory_cell_texture
                    [hand_cell_button_vector[i].getStatus()][0]);

            hand_cell_button_vector[i].setCount(
                Player::getInstance()->getHandCell(i).getCount());

            StorageCell& st_cell = Player::getInstance()->getHandCell(i);

            updateTransfer(i, st_cell, TransferCell::StorageType::HAND);
            updateStorageObjectTexture(st_cell, hand_cell_button_vector[i]);
        }
        // intermediate_buffer.update();
    }
end:
    return;
}

void
Gui::Graphic::InventoryInterface::drawUsingCells()
{
    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        hand_cell_button_vector[i].draw();
    }
}

void
Gui::Graphic::InventoryInterface::drawFullInventory()
{

    Gui::getInstance()->m_window.draw(background);

    // Gui::getInstance()->m_window.draw(up_arrow_button.getShapePtr());
    // Gui::getInstance()->m_window.draw(down_arrow_button.getShapePtr());

    for (int i = 0; i < inventory_cell_button_vector.size(); ++i)
    {

        int index_inventory = shift * row_length + i;

        if (index_inventory >= Player::getInstance()->getInventorySize()) break;
        inventory_cell_button_vector[i].draw();
    }
    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        hand_cell_button_vector[i].draw();
    }
    if (!transfer_cell.isClear())
    {
        sf::Vector2f mouse_pos = Gui::getInstance()->getMousePosition();
        float cell_length = transfer_cell.inventory_cell_button.getSize().x;

        transfer_cell.inventory_cell_button.setPosition(
            {mouse_pos.x - cell_length, mouse_pos.y});
        // std::cout <<
        // transfer_cell.inventory_cell_button.getTextureRect().left
        //           << '\n';
        transfer_cell.inventory_cell_button.draw();
    }
}

const StorageCell&
Gui::Graphic::InventoryInterface::getUsingStorageCellRef()
{
    return Player::getInstance()->getHandCell(index_using_hand);
}

Gui::Graphic::InventoryInterface::Status
Gui::Graphic::InventoryInterface::getStatus()
{
    return status;
}