#include "tree.hpp"

#include "storage/instrument.hpp"

const int Tree::MAX_STRENGTH = 100;

Tree::Tree(Type t) : PhysicalObject(t, {1, 1})
{
    picture_shift = {1, 4};
    picture_size  = {3, 5};

    strength = 20;
}

bool
Tree::isObstructive() const
{
    return true;
}
