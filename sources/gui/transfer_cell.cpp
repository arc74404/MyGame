#include <iostream>

#include "gui.hpp"
#include "texture_storage.hpp"
Gui::Graphic::InventoryInterface::TransferCell::TransferCell()
{
    index = -1;

    // inventory_cell_button.setTexture()
}

void
Gui::Graphic::InventoryInterface::TransferCell::setData(
    TransferCell::StorageType storage_tt, int ii,
    const std::shared_ptr<StorageObject> st_obj, int c)
{
    storage_type = storage_tt;

    index = ii;

    m_count = c;

    this->storage_object_ptr = st_obj->getCopyObject();

    inventory_cell_button.setCount(c);

    int ind = 0;
    if (st_obj->getGeneralType() == StorageObject::GeneralType::INSTRUMENT)
    {
        ind =
            std::reinterpret_pointer_cast<const Instrument>(st_obj)->geLevel();
    }
    // std::cout << "setTextureRect\n";
    // std::cout << TextureStorage::getInstance()
    //                  ->storage_objects_texture[st_obj->getType()][ind]
    //                  .left
    //           << '\n';
    inventory_cell_button.setInventoryObjectTextureRect(
        TextureStorage::getInstance()
            ->storage_objects_texture[st_obj->getType()][ind]);
    // std::cout << inventory_cell_button.getTextureRect().left << '\n';
}

Gui::Graphic::InventoryInterface::TransferCell::StorageType
Gui::Graphic::InventoryInterface::TransferCell::getStorageType()
{
    return storage_type;
}

int
Gui::Graphic::InventoryInterface::TransferCell::getIndex()
{
    return index;
}

bool
Gui::Graphic::InventoryInterface::TransferCell::isClear()
{
    return !m_count;
}

void
Gui::Graphic::InventoryInterface::TransferCell::clear()
{
    StorageCell::clear();
    index = -1;
    inventory_cell_button.setCount(0);
    inventory_cell_button.setTextureRect({0, 0, 0, 0});
}