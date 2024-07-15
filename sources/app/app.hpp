#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>

class App
{
public:
    static App* getInstance();

    void run();

    sf::Time getCycleTime();

    void finishWork();

private:
    App();

    bool is_work;

    sf::Clock m_clock;

    sf::Time cycle_time;
};

#endif // APP_HPP