#include <iostream>

#include "gui.hpp"
#include "math.h"

MyTexture<BaseButton::Status>
    Gui::Graphic::InventoryInterface::inventory_cell_texture;

MyTexture<BaseButton::Status>
    Gui::Graphic::InventoryInterface::up_down_button_texture;

MyTexture<Instrument::InstrumentType>
    Gui::Graphic::InventoryInterface::instruments_texture;

void
Gui::Graphic::InventoryInterface::loadTexture()
{
    inventory_cell_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/cell_storage_texture.png");

    up_down_button_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/arrow_button.png");

    sf::IntRect r = {27, 11, 88, 116};

    up_down_button_texture[BaseButton::Status::NOT_SHINE].emplace_back(r);

    r.left += 103;
    up_down_button_texture[BaseButton::Status::HIGHLIGHTED].emplace_back(r);

    r.left += 104;
    up_down_button_texture[BaseButton::Status::SHINE].emplace_back(r);

    r = {42, 58, 73, 67};
    inventory_cell_texture[BaseButton::Status::NOT_SHINE].emplace_back(r);

    r.left += 90;
    inventory_cell_texture[BaseButton::Status::HIGHLIGHTED].emplace_back(r);

    r.left += 90;
    inventory_cell_texture[BaseButton::Status::SHINE].emplace_back(r);

    instruments_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/instruments.png");

    r = {40, 165, 110, 110};

    instruments_texture[Instrument::InstrumentType::AXE].emplace_back(r);

    r.left += 123;
    instruments_texture[Instrument::InstrumentType::AXE].emplace_back(r);

    r.left += 126;
    instruments_texture[Instrument::InstrumentType::AXE].emplace_back(r);

    r = {38, 17, 120, 123};
    instruments_texture[Instrument::InstrumentType::PICKAXE].emplace_back(r);

    r.left += 123;
    instruments_texture[Instrument::InstrumentType::PICKAXE].emplace_back(r);

    r.left += 123;
    instruments_texture[Instrument::InstrumentType::PICKAXE].emplace_back(r);
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
    if (objPtr->getType() != StorageObject::Type::HAND)
    {
        if (objPtr->getType() == StorageObject::Type::INSTRUMENT)
        {
            std::shared_ptr<Instrument> instrumentPtr =
                std::static_pointer_cast<Instrument>(objPtr);

            inv_cell_button.setInventoryObjectTexture(
                instruments_texture.getTexturePtr());

            int_rect = instruments_texture[instrumentPtr->getInstrumentType()]
                                          [instrumentPtr->geLevel()];
        }
    }

    inv_cell_button.setInventoryObjectTextureRect(int_rect);
}

void
Gui::Graphic::InventoryInterface::update()
{
    static isKeyboardButtonClickedOff is_tab_clicked_off;
    is_tab_clicked_off.setKey(sf::Keyboard::Tab);

    if (status == Status::CLOSE)
    {
        if (is_tab_clicked_off())
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
                inventory_cell_texture[hand_cell_button_vector[i].getStatus()]
                                      [0]);
            updateStorageObjectTexture(Player::getInstance()->getHandCell(i),
                                       hand_cell_button_vector[i]);
        }
    }
    else if (status == Status::OPEN)
    {
        // static const BaseButton* t1 = &up_arrow_button;
        // static const BaseButton* t2 = &down_arrow_button;

        // static isDefaultButtonClickedOff is_up_arrow_button_clicked_off(t1);

        // static isDefaultButtonClickedOff
        // is_down_arrow_button_clicked_off(t2);

        // if (is_up_arrow_button_clicked_off())
        // {
        //     lowerShift();
        // }
        // else if (is_down_arrow_button_clicked_off())
        // {
        //     raiseShift();
        // }
        if (is_tab_clicked_off())
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

        for (int i = 0; i < inventory_cell_button_vector.size(); ++i)
        {
            inventory_cell_button_vector[i].update();
            inventory_cell_button_vector[i].setTextureRect(
                inventory_cell_texture[inventory_cell_button_vector[i]
                                           .getStatus()][0]);

            int index_inventory = shift * row_length + i;

            if (index_inventory >= Player::getInstance()->getInventorySize())
                break;

            StorageCell& st_cell =
                Player::getInstance()->getInventoryCell(index_inventory);

            // if (st_cell.getObject()->getType() != StorageObject::Type::HAND
            // &&
            //     inventory_cell_button_vector[i].getStatus() ==
            //         BaseButton::Status::SHINE)
            // {
            //     intermediate_buffer.moveInBuffer(
            //         IntermediateBuffer::StorageType::INVENTORY,
            //         index_inventory);
            // }
            // else if (st_cell.getObject()->getType() ==
            //              StorageObject::Type::HAND &&
            //          inventory_cell_button_vector[i].getStatus() ==
            //              BaseButton::Status::HIGHLIGHTED &&
            //          inventory_cell_button_vector[i].isPointInButton(
            //              Gui::getInstance()->getMousePosition()) &&
            //          intermediate_buffer.getIndex() != -1)
            // {
            //     intermediate_buffer.moveFromBuffer(
            //         IntermediateBuffer::StorageType::INVENTORY,
            //         index_inventory);
            // }

            updateStorageObjectTexture(st_cell,
                                       inventory_cell_button_vector[i]);
        }

        for (int i = 0; i < hand_cell_button_vector.size(); ++i)
        {
            static_cast<InventoryCellButton*>(&hand_cell_button_vector[i])
                ->update();

            hand_cell_button_vector[i].setTextureRect(
                inventory_cell_texture[hand_cell_button_vector[i].getStatus()]
                                      [0]);

            const StorageCell& st_cell = Player::getInstance()->getHandCell(i);

            // if (st_cell.getObject()->getType() != StorageObject::Type::HAND
            // &&
            //     hand_cell_button_vector[i].getStatus() ==
            //         BaseButton::Status::SHINE)
            // {
            //     intermediate_buffer.moveInBuffer(
            //         IntermediateBuffer::StorageType::HAND, i);
            // }
            // else if (st_cell.getObject()->getType() ==
            //              StorageObject::Type::HAND &&
            //          hand_cell_button_vector[i].getStatus() ==
            //              BaseButton::Status::HIGHLIGHTED &&
            //          hand_cell_button_vector[i].isPointInButton(
            //              Gui::getInstance()->getMousePosition()) &&
            //          intermediate_buffer.getIndex() != -1)
            // {
            //     intermediate_buffer.moveFromBuffer(
            //         IntermediateBuffer::StorageType::HAND, i);
            // }

            updateStorageObjectTexture(st_cell, hand_cell_button_vector[i]);
        }
        intermediate_buffer.update();
    }
end:
    return;
}

void
Gui::Graphic::InventoryInterface::create()
{
    shift = 0;

    sf::Vector2f window_size = Gui::getInstance()->getWindowSize();
    sf::Vector2f b_size      = {window_size.x * 0.6f, window_size.y * 0.8f};
    sf::Vector2f b_pos       = {(window_size.x - b_size.x) * 0.5f,
                                (window_size.y - b_size.y) * 0.5f};

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
                inventory_cell_texture.getTexturePtr());

            inventory_cell_button_vector[index].setInventoryObjectTexture(
                instruments_texture.getTexturePtr());

            inventory_cell_button_vector[index].setTextureRect(
                inventory_cell_texture[BaseButton::Status::NOT_SHINE][0]);

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
            instruments_texture.getTexturePtr());

        hand_cell_button_vector[i].setInventoryObjectTextureRect({0, 0, 0, 0});

        hand_cell_button_vector[i].setTexture(
            inventory_cell_texture.getTexturePtr());

        hand_cell_button_vector[i].setTextureRect(
            inventory_cell_texture[BaseButton::Status::NOT_SHINE][0]);
    }
    close();
}

void
Gui::Graphic::InventoryInterface::drawUsingCells()
{
    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        Gui::getInstance()->m_window.draw(
            hand_cell_button_vector[i].getShapeRef());
        Gui::getInstance()->m_window.draw(
            hand_cell_button_vector[i].getInventoryObjectShapeRef());
        for (int j = 0;
             j <
             hand_cell_button_vector[i].getObjectCountShapeVectorRef().size();
             ++j)
        {
            Gui::getInstance()->m_window.draw(
                hand_cell_button_vector[i].getObjectCountShapeVectorRef()[j]);
        }
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

        Gui::getInstance()->m_window.draw(
            inventory_cell_button_vector[i].getShapeRef());
        Gui::getInstance()->m_window.draw(
            inventory_cell_button_vector[i].getInventoryObjectShapeRef());

        for (int j = 0; j < inventory_cell_button_vector[i]
                                .getObjectCountShapeVectorRef()
                                .size();
             ++j)
        {
            Gui::getInstance()->m_window.draw(
                inventory_cell_button_vector[i]
                    .getObjectCountShapeVectorRef()[j]);
        }
    }
    for (int i = 0; i < hand_cell_button_vector.size(); ++i)
    {
        Gui::getInstance()->m_window.draw(
            hand_cell_button_vector[i].getShapeRef());

        Gui::getInstance()->m_window.draw(
            hand_cell_button_vector[i].getInventoryObjectShapeRef());

        for (int j = 0;
             j <
             hand_cell_button_vector[i].getObjectCountShapeVectorRef().size();
             ++j)
        {
            Gui::getInstance()->m_window.draw(
                hand_cell_button_vector[i].getObjectCountShapeVectorRef()[j]);
        }
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