#include "world_state_saver.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "player/player.hpp"
int WorldStateSaver::total_number_savers = 0;

WorldStateSaver::WorldStateSaver()
{
    m_id = -1;
}

std::string
WorldStateSaver::getPath(int id)
{
    std::string res = "C:/Users/arsbo/source/repos/game2/resources/mapStates/";
    res += "world_save_";
    res += std::to_string(id);
    return res;
}

void
WorldStateSaver::loadWorld()
{
}

void
WorldStateSaver::saveWorld()
{
    if (m_id == -1)
    {
        m_id = total_number_savers++;

        std::string path = getPath(m_id);

        std::ofstream output_file(path, std::ios::binary);

        try
        {
            if (output_file.is_open())
            {
                throw std::exception(
                    std::string("can not open file: " + path).c_str());
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        Player::getInstance()->saveToFile(output_file);
        World::getInstance()->saveToFile(output_file);
    }
    else
    {
    }
}