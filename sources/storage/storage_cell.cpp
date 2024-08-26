#include "storage_cell.hpp"

#include <iostream>

#include "resource.hpp"
int StorageCell::count_limit = 30;

int
StorageCell::getCountLimit()
{
    return count_limit;
}

StorageCell::StorageCell()
{
    storage_object_ptr = NULL;
}

void
StorageCell::swap(StorageCell& first, StorageCell& second)
{
    StorageCell extra = first;
    first             = second;
    second            = extra;
}

void
StorageCell::setObject(StorageObjectPtr obj_ptr, int count)
{
    storage_object_ptr = obj_ptr;

    m_count = count;

    if (storage_object_ptr->getType() == StorageObject::Type::HAND) m_count = 0;
}

void
StorageCell::setCount(int c)
{
    m_count = c;
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
StorageCell::getCount() const
{
    return m_count;
}

void
StorageCell::operator=(const StorageCell& other)
{
    // std::cout << int(other.storage_object_ptr->getType()) << '\n';
    this->storage_object_ptr = other.storage_object_ptr->getCopyObject();

    this->m_count = other.m_count;
}