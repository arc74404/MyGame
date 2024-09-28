#ifndef MAP_STATE_SAVER_HPP
#define MAP_STATE_SAVER_HPP
#include <string>

class WorldStateSaver
{
public:
    class WorldStateSaverStorage
    {
    };

    WorldStateSaver();

    void loadWorld();

    void saveWorld();

private:
    static std::string getPath(int id);

    static int total_number_savers;

    int m_id;
};

#endif // !MAP_STATE_SAVER_HPP