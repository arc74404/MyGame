#ifndef CRAFT_MENU_HPP
#define CRAFT_MENU_HPP

#include "storage.hpp"

class CraftMenu
{
public:
    struct CraftRow
    {
        static int MAX_COUNT_CELL_FOR_INGREDIENTS;

        bool isAvailableForCraft() const;

        StorageCell result_object;

        std::vector<StorageCell> ingredient_vector;

        bool required_level;
    };

    CraftMenu();

    CraftRow createCraftRow(bool required_level, StorageObjectPtr st_obj_ptr,
                            int count,
                            const std::vector<StorageCell>& ingredient_vector);

    const CraftRow& getCraftRow(int index) const;

    int getRowCount() const;

    void setLevel(bool ll);

private:
    std::vector<StorageCell> getIngredientsPickaxeLevel0();
    std::vector<StorageCell> getIngredientsPickaxeLevel1();
    std::vector<StorageCell> getIngredientsPickaxeLevel2();

    std::vector<StorageCell> getIngredientsAxeLevel0();
    std::vector<StorageCell> getIngredientsAxeLevel1();
    std::vector<StorageCell> getIngredientsAxeLevel2();

    bool level; // there are only two levels

    std::vector<CraftRow> craft_selection;
};

#endif // CRAFT_MENU_HPP