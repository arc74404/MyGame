#ifndef STORAGE_CELL_HPP
#define STORAGE_CELL_HPP

#include <shared_mutex>

#include "gui/inventory_cell_button.hpp"

#include "storage_object.hpp"

typedef std::shared_ptr<StorageObject> StorageObjectPtr;

class StorageCell
{
public:
    StorageCell();

    static void swap(StorageCell& first, StorageCell& second);

    void setObject(StorageObjectPtr obj_ptr, int count = 1);

    void setCount(int c);

    const StorageObjectPtr getObject() const;

    virtual void clear();

    int getCount() const;

    void operator=(const StorageCell& other);

    static int getCountLimit();

protected:
    static int count_limit;

    StorageObjectPtr storage_object_ptr;

    int m_count;
};

#endif // !STORAGE_CELL_HPP