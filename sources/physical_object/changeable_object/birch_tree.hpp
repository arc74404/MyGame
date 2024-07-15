#ifndef BIRCH_TREE_HPP
#define BIRCH_TREE_HPP

#include "tree.hpp"

class BirchTree : public Tree
{
public:
    BirchTree();

    void update() override;

    int getPictureIndex() const override;

private:
};

#endif // !BIRCH_TREE_HPP