#ifndef TREE_HPP
#define TREE_HPP

#include "physical_object/physical_object.hpp"

class Tree : public PhysicalObject
{
public:
    Tree(Type t);

    virtual void update() = 0;

    virtual int getPictureIndex() const = 0;

    bool isObstructive() const override;

private:
    Type tree_type;

    static const int MAX_STRENGTH;
};

#endif // !TREE_HPP