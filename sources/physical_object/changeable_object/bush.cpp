#include "bush.hpp"

#include "app/app.hpp"

const int Bush::MAX_BERRY_COUNT = 100;
const int Bush::MAX_STRENGTH    = 100;

Bush::Bush(Type bt) : PhysicalObject(bt, {1, 1}, 100), berry_count(0)
{
    picture_shift = {0, 0};
    picture_size  = {1, 1};
}

void
Bush::update()
{
    double time_passed = update_clock.restart().asSeconds();


    berry_count += (time_passed * 2);

    if (berry_count > MAX_BERRY_COUNT)
    {
        berry_count = MAX_BERRY_COUNT;
    }
}

int
Bush::getPictureIndex() const
{
    int ind = (berry_count / MAX_BERRY_COUNT) * 100 / 25;

    if (ind >= 4) ind = 3;
    return ind;
}

bool
Bush::isObstructive() const
{
    return false;
}