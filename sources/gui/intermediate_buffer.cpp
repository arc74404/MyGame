#include <iostream>

#include "gui.hpp"
Gui::Graphic::InventoryInterface::IntermediateBuffer::IntermediateBuffer()
{
    // index = -1;
}

void
Gui::Graphic::InventoryInterface::IntermediateBuffer::update()
{
    // if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    // {
    //     index = -1;
    // }
}

void
Gui::Graphic::InventoryInterface::IntermediateBuffer::moveInBuffer(
    StorageType storage_tt, int ii)
{
    // storage_cell_ptr
    // index                  = ii;
    // from_what_storage_type = storage_tt;
}

void
Gui::Graphic::InventoryInterface::IntermediateBuffer::moveFromBuffer(
    StorageType storage_tt, int ii)
{

    // if (from_what_storage_type == IntermediateBuffer::StorageType::INVENTORY)
    // {
    //     if (storage_tt == IntermediateBuffer::StorageType::INVENTORY)
    //     {
    //         StorageCell::swap(&Player::getInstance()->getInventoryCell(ii),
    //                           &Player::getInstance()->getInventoryCell(index));
    //         // Player::getInstance()->getInventoryCell(ii).setObject(
    //         // Player::getInstance()->getInventoryCell(index).getObject());
    //     }
    //     else if (storage_tt == IntermediateBuffer::StorageType::HAND)
    //     {
    //         Player::getInstance()->getHandCell(ii).setObject(
    //             Player::getInstance()->getInventoryCell(index).getObject());
    //     }
    //     Player::getInstance()->getInventoryCell(index).setObject(
    //         std::make_shared<StorageObject>(
    //             StorageObject(StorageObject::Type::EMPTY)));
    // }
    // else if (from_what_storage_type == IntermediateBuffer::StorageType::HAND)
    // {
    //     if (storage_tt == IntermediateBuffer::StorageType::INVENTORY)
    //     {
    //         Player::getInstance()->getInventoryCell(ii).setObject(
    //             Player::getInstance()->getHandCell(index).getObject());
    //     }
    //     else if (storage_tt == IntermediateBuffer::StorageType::HAND)
    //     {
    //         Player::getInstance()->getHandCell(ii).setObject(
    //             Player::getInstance()->getHandCell(index).getObject());
    //     }
    //     Player::getInstance()->getHandCell(index).setObject(
    //         std::make_shared<StorageObject>(
    //             StorageObject(StorageObject::Type::EMPTY)));
    // }

    // index = -1;
}

int
Gui::Graphic::InventoryInterface::IntermediateBuffer::getIndex()
{
    // return index;
    return 0;
}