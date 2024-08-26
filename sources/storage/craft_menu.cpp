#include "craft_menu.hpp"

#include "player/player.hpp"

#include "instrument.hpp"
#include "resource.hpp"

int CraftMenu::CraftRow::MAX_COUNT_CELL_FOR_INGREDIENTS = 5;

CraftMenu::CraftRow
CraftMenu::createCraftRow(bool required_level, StorageObjectPtr st_obj_ptr,
                          int count, const std::vector<StorageCell>& ing_vector)
{
    CraftRow craft_row;

    craft_row.required_level = required_level;
    craft_row.result_object.setObject(st_obj_ptr, count);
    craft_row.ingredient_vector = ing_vector;

    return craft_row;
}

std::vector<StorageCell>
CraftMenu::getIngredientsPickaxeLevel0()
{
    std::vector<StorageCell> res;

    StorageCell st_cell;

    st_cell.setObject(
        std::make_shared<Resource>(Resource(StorageObject::Type::WOOD)));
    st_cell.setCount(3);

    res.emplace_back(st_cell);
    return res;
}
std::vector<StorageCell>
CraftMenu::getIngredientsPickaxeLevel1()
{
    std::vector<StorageCell> res;

    StorageCell st_cell;

    st_cell.setObject(
        std::make_shared<Resource>(Resource(StorageObject::Type::WOOD)));
    st_cell.setCount(2);

    res.emplace_back(st_cell);

    st_cell.setObject(
        std::make_shared<Resource>(Resource(StorageObject::Type::STONE)));
    st_cell.setCount(3);

    res.emplace_back(st_cell);
    return res;
}
std::vector<StorageCell>
CraftMenu::getIngredientsPickaxeLevel2()
{
    std::vector<StorageCell> res;

    StorageCell st_cell;

    st_cell.setObject(
        std::make_shared<Resource>(Resource(StorageObject::Type::WOOD)));
    st_cell.setCount(4);

    res.emplace_back(st_cell);

    st_cell.setObject(
        std::make_shared<Resource>(Resource(StorageObject::Type::STONE)));
    st_cell.setCount(4);

    res.emplace_back(st_cell);
    return res;
}

std::vector<StorageCell>
CraftMenu::getIngredientsAxeLevel0()
{
    return getIngredientsPickaxeLevel0();
}
std::vector<StorageCell>
CraftMenu::getIngredientsAxeLevel1()
{
    return getIngredientsPickaxeLevel1();
}
std::vector<StorageCell>
CraftMenu::getIngredientsAxeLevel2()
{
    return getIngredientsPickaxeLevel2();
}

CraftMenu::CraftMenu()
{
    StorageObjectPtr st_obj_ptr;
    /////////////////////////////////////////////////////////////////////////
    st_obj_ptr = std::make_shared<Instrument>(
        Instrument(StorageObject::Type::PICKAXE, 0));
    craft_selection.emplace_back(
        createCraftRow(0, st_obj_ptr, 1, getIngredientsPickaxeLevel0()));
    /////////////////////////////////////////////////////////////////////////
    st_obj_ptr = std::make_shared<Instrument>(
        Instrument(StorageObject::Type::PICKAXE, 1));
    craft_selection.emplace_back(
        createCraftRow(1, st_obj_ptr, 1, getIngredientsPickaxeLevel1()));
    /////////////////////////////////////////////////////////////////////////
    st_obj_ptr = std::make_shared<Instrument>(
        Instrument(StorageObject::Type::PICKAXE, 2));
    craft_selection.emplace_back(
        createCraftRow(1, st_obj_ptr, 1, getIngredientsPickaxeLevel2()));
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    st_obj_ptr =
        std::make_shared<Instrument>(Instrument(StorageObject::Type::AXE, 0));
    craft_selection.emplace_back(
        createCraftRow(0, st_obj_ptr, 1, getIngredientsAxeLevel0()));
    /////////////////////////////////////////////////////////////////////////
    st_obj_ptr =
        std::make_shared<Instrument>(Instrument(StorageObject::Type::AXE, 1));
    craft_selection.emplace_back(
        createCraftRow(1, st_obj_ptr, 1, getIngredientsAxeLevel1()));
    /////////////////////////////////////////////////////////////////////////
    st_obj_ptr =
        std::make_shared<Instrument>(Instrument(StorageObject::Type::AXE, 2));
    craft_selection.emplace_back(
        createCraftRow(1, st_obj_ptr, 1, getIngredientsAxeLevel2()));
    /////////////////////////////////////////////////////////////////////////
}

const CraftMenu::CraftRow&
CraftMenu::getCraftRow(int index) const
{
    return craft_selection[index];
}

void
CraftMenu::setLevel(bool ll)
{
    level = ll;
}

// void
// CraftMenu::update()
// {
//     for (int i = 0; i < craft_selection.size(); ++i)
//     {
//         if (craft_selection[i].required_level <= level &&
//             Player::getInstance()->checkIngredientsSufficiency(
//                 craft_selection[i].ingredient_vector))
//         {
//             craft_selection[i].can_craft = true;
//         }
//     }
// }

int
CraftMenu::getRowCount() const
{
    return craft_selection.size();
}

bool
CraftMenu::CraftRow::isAvailableForCraft() const
{
    return Player::getInstance()->checkIngredientsSufficiency(
        ingredient_vector);
}