#ifndef BUSH_HPP
#define BUSH_HPP

#include "physical_object/physical_object.hpp"

class Bush : public PhysicalObject
{
public:
    Bush(Type bt);

    void update() override;

    int getPictureIndex() const override;

    bool isObstructive() const override;

private:
    static const int MAX_BERRY_COUNT;

    float berry_count;

    static const int MAX_STRENGTH;
};

#endif // BUSH_HPP