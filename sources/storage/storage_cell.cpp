#include "storage_cell.hpp"

StorageCell::StorageCell()
{
    storage_object_ptr = NULL;
}

void
StorageCell::swap(StorageCell* first, StorageCell* second)
{
    first->storage_object_ptr.swap(second->storage_object_ptr);
}

void
StorageCell::setObject(StorageObjectPtr obj_ptr, int count)
{
    storage_object_ptr = obj_ptr;

    m_count = count;

    if (storage_object_ptr->getType() == StorageObject::Type::HAND) m_count = 0;
}

const StorageObjectPtr
StorageCell::getObject() const
{
    return storage_object_ptr;
}

void
StorageCell::clear()
{
    storage_object_ptr = std::make_shared<StorageObject>(
        StorageObject(StorageObject::Type::HAND));
    m_count = 0;
}

int
StorageCell::getCount()
{
    return m_count;
}