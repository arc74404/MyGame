#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <vector>

#include "storage_cell.hpp"

class Storage : public std::vector<StorageCell>
{
public:
    Storage();

private:
};

#endif //! STORAGE_HPP