#include "block.hpp"

Block::Block(BlockType bt) : StorageObject(StorageObject::Type::BLOCK)
{
    block_type = bt;
}

Block::BlockType
Block::getBlockType()
{
    return block_type;
}