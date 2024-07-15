#include "apple_tree.hpp"

const int AppleTree::MAX_APPLE_COUNT = 100;

AppleTree::AppleTree() : Tree(Type::APPLE_TREE)
{
    apple_count = 0;
}

void
AppleTree::update()
{
    double time_passed = update_clock.restart().asSeconds();

    apple_count += (time_passed * 2);

    if (apple_count > MAX_APPLE_COUNT)
    {
        apple_count = MAX_APPLE_COUNT;
    }
}

int
AppleTree::getPictureIndex() const
{
    int pr = (apple_count / MAX_APPLE_COUNT) * 100;
    int ind;

    if (pr < 25) ind = 0;
    else if (pr < 50) ind = 1;
    else if (pr < 75) ind = 2;
    else ind = 3;

    return ind;
}