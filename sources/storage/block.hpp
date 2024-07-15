#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "storage/storage_object.hpp"

class Block : public StorageObject
{
public:
    enum class BlockType
    {
        DOOR = 0,
        WALL = 1
    };

    Block(BlockType bt);

    BlockType getBlockType();

private:
    BlockType block_type;
};

#endif // !BLOCK_HPP
