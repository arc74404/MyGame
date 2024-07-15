#ifndef STONE_HPP
#define STONE_HPP

#include "physical_object/physical_object.hpp"
#include "storage/storage_object.hpp"

class Stone : public PhysicalObject
{
public:
    Stone();

    void update() override;

    int getPictureIndex() const override;

    bool isObstructive() const override;

    bool isCorrrectInstrument(const StorageObject& st_obj) const;

private:
    static const int MAX_STRENGTH;
};

#endif // STONE_HPP