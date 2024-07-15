#ifndef GRASS_HPP
#define GRASS_HPP

#include "physical_object/physical_object.hpp"

class Grass : public PhysicalObject
{
public:
    Grass();

    void update() override;

    int getPictureIndex() const override;

    bool isObstructive() const override;

private:
    static const int MAX_LENGTH;

    float length;
};

#endif // GRASS_HPP