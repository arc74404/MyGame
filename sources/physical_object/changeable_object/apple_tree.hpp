#ifndef APPLE_TREE_HPP
#define APPLE_TREE_HPP

#include "tree.hpp"

class AppleTree : public Tree
{
public:
    AppleTree();

    void update() override;

    int getPictureIndex() const override;

private:
    static const int MAX_APPLE_COUNT;

    float apple_count;
};

#endif // !APPLE_TREE_HPP