#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "storage/storage.hpp"
#include "world/cell.hpp"

class Player
{
public:
    enum class Flank
    {
        LEFT  = 0,
        RIGHT = 1
    };

private:
    struct MovementData
    {
        sf::Vector2f m_position;

        sf::Vector2f next_position;

        float walk_time_seconds;

        float speed;

        Flank m_flank;
    };

    struct CollisionData
    {
        float base_length;
        float base_width;
    };

public:
    enum class Status
    {
        STAND = 0,
        WALK  = 1
    };

public:
    static Player* getInstance();

    void update();

    void moveNextPosition(const sf::Vector2f&);

    void stopMoving();

    void operate(const WorldCell&, const StorageCell&);

    void restartTimeRechargeAsSeconds(float tt);

    bool isReadyToHit();

    ////////////////////////////

    StorageCell& getInventoryCell(int index);

    StorageCell& getHandCell(int index);

    Status getStatus();

    sf::Vector2f getPosition();

    float getWalkTimeSeconds();

    Flank getFlank();

    float getProcentHealth();

    float getProcentHunger();

    float getFullRechargeTimeAsSeconds();
    float getLeftRechargeTimeAsSeconds();

    int getInventorySize();

    int getHandVectorSize();

private:
    //////////////////////////////////////////
    void walk();
    void die();
    //////////////////////////////////////////

    ///////////////////////////////////////////
    void align(sf::IntRect);

    void handleCollision();

    Player();

    Status m_status;

    MovementData movement_data;
    CollisionData collision_data;

    Storage inventory;

    Storage hand_vector;

    const WorldCell* world_cell_ptr;

    sf::Clock clock_recharge;
    float time_recharge_seconds;

    ////////////////////////////////

    float hunger;
    const float MAX_HUNGER = 100;

    float health;
    const float MAX_HEALTH = 100;
};

#endif // PLAYER_HPP