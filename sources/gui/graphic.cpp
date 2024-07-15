
#include <iostream>

#include "app/app.hpp"
#include "player/player.hpp"
#include "world/cell.hpp"
#include "world/location.hpp"
#include "world/world.hpp"

#include "gui.hpp"

Gui::Graphic::Graphic()
{
    rendering_radius = 4;
}

void
Gui::Graphic::loadObjectTexture()
{
    physical_object_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/object_"
        "texture.png");

    physical_object_texture[PhysicalObject::Type::STONE].emplace_back(
        sf::IntRect(17, 17, 53, 50));

    physical_object_texture[PhysicalObject::Type::GRASS].emplace_back(
        sf::IntRect(12 + 71 * 2, 224, 70, 63));

    physical_object_texture[PhysicalObject::Type::APPLE_TREE].emplace_back(
        sf::IntRect(360, 50, 150, 145));

    physical_object_texture[PhysicalObject::Type::APPLE_TREE].emplace_back(
        sf::IntRect(360 + 165, 50, 150, 145));

    physical_object_texture[PhysicalObject::Type::APPLE_TREE].emplace_back(
        sf::IntRect(360, 50 + 160, 150, 145));

    physical_object_texture[PhysicalObject::Type::APPLE_TREE].emplace_back(
        sf::IntRect(360 + 165, 50 + 160, 150, 145));

    physical_object_texture[PhysicalObject::Type::BIRCH_TREE].emplace_back(
        sf::IntRect(360 + 354, 52, 150, 145));

    for (int i = 0; i < 4; ++i)
    {
        physical_object_texture[PhysicalObject::Type::BUSH_BLUEBERRY]
            .emplace_back(sf::IntRect(12 + 71 * i, 81, 70, 63));
        physical_object_texture[PhysicalObject::Type::BUSH_STRAWBERRY]
            .emplace_back(sf::IntRect(12 + 71 * i, 150, 70, 63));
    }
}

void
Gui::Graphic::loadCharTexture()
{
    char_texture.loadFromFile("C:/Users/arsbo/source/repos/game2/resources/"
                              "char_symbols.png");
    sf::IntRect int_rect(7, 6, 8, 10);
    // char_texture['0'].emplace_back(int_rect);
    for (char c = '0'; c <= '2'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 9;
    }
    int_rect.left += 1;
    for (char c = '3'; c <= '9'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 10;
    }
    for (char c = 'a'; c <= 'h'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 10;
    }
    int_rect.left -= 1;
    for (char c = 'i'; c <= 'j'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 9;
    }
    int_rect.left += 1;
    for (char c = 'k'; c < 'm'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 10;
    }
    int_rect.width += 2;
    char_texture['m'].emplace_back(int_rect);
    int_rect.width -= 2;
    int_rect.left += 12;
    for (char c = 'n'; c <= 's'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 10;
    }
    int_rect.width += 2;
    char_texture['t'].emplace_back(int_rect);
    int_rect.width -= 2;
    int_rect.left += 12;
    for (char c = 'u'; c <= 'u'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 10;
    }
    int_rect.width += 2;
    char_texture['v'].emplace_back(int_rect);
    int_rect.left += 12;
    for (char c = 'v'; c <= 'z'; c++)
    {
        char_texture[c].emplace_back(int_rect);
        int_rect.left += 11;
    }

    int_rect.top  = 24;
    int_rect.left = 6;
    char_texture['!'].emplace_back(int_rect);
    int_rect.left += 10;
    char_texture['#'].emplace_back(int_rect);
    int_rect.left += 11;
    char_texture['%'].emplace_back(int_rect);
    int_rect.left += 9;
    char_texture['-'].emplace_back(int_rect);
    int_rect.left += 8;
    char_texture['+'].emplace_back(int_rect);
    int_rect.left += 8;
    char_texture['.'].emplace_back(int_rect);
}

void
Gui::Graphic::loadTextures()
{
    Gui::Graphic::Indicator::loadTexture();
    Gui::Graphic::InventoryInterface::loadTexture();

    loadCharTexture();

    player_interface.loadTextures();

    inventory_interface.create();

    loadObjectTexture();

    zoom(2.5f);
}

void
Gui::Graphic::drawWorld()
{

    static sf::Color transparent(0, 0, 0, 0);
    sf::Vector2f player_position = Player::getInstance()->getPosition();

    int cell_length = WorldCell::getLength();

    int location_cell_length = Location::getLength();

    int location_length = location_cell_length * cell_length;

    sf::Vector2i cell_position;

    sf::Vector2f player_position_window = getPlayerPositionInWindow();

    sf::Vector2i player_location_coordinate = {
        int(player_position.x) / location_length,
        int(player_position.y) / location_length};

    sf::Vector2i player_cell_on_world =
        World::getInstance()->getCellPosition(player_position);

    int player_line_y = player_cell_on_world.y % location_cell_length;

    // std::cout << player_line_y << '\n';
    for (int w_y = player_location_coordinate.y - rendering_radius;
         w_y <= player_location_coordinate.y + rendering_radius; ++w_y)
    {
        for (int l_y = 0; l_y < location_cell_length; ++l_y)
        {
            for (int w_x = player_location_coordinate.x - rendering_radius;
                 w_x <= player_location_coordinate.x + rendering_radius; ++w_x)
            {
                if (w_x < 0 || w_y < 0 ||
                    w_x >= World::getInstance()->getLength() ||
                    w_y >= World::getInstance()->getLength())
                {
                    continue;
                }
                if (player_line_y == l_y &&
                    w_x == player_location_coordinate.x + 1 &&
                    player_location_coordinate.y == w_y)
                {
                    player_interface.drawPlayer();
                }

                for (int l_x = 0; l_x < location_cell_length; ++l_x)
                {

                    const Location& location =
                        World::getInstance()->getLocation(w_x, w_y);

                    cell_position = {w_x * location_cell_length * cell_length +
                                         l_x * cell_length,
                                     w_y * location_cell_length * cell_length +
                                         l_y * cell_length};

                    sf::Vector2f difference;

                    difference.x =
                        (player_position.x - cell_position.x) * scope;
                    difference.y =
                        (player_position.y - cell_position.y) * scope;

                    const WorldCell& p_cell = location.getCell(l_x, l_y);

                    sf::RectangleShape shape;

                    if (p_cell.isMain() && !p_cell.isEmpty())
                    {
                        sf::Vector2i picture_shift =
                            p_cell.getObjectPtr()->getPictureShift();

                        sf::Vector2i picture_size =
                            p_cell.getObjectPtr()->getPictureSize();

                        shape.setSize({cell_length * picture_size.x * scope,
                                       cell_length * picture_size.y * scope});

                        sf::Vector2f pos = player_position_window - difference;

                        shape.setPosition(
                            {pos.x - picture_shift.x * cell_length * scope,
                             pos.y - picture_shift.y * cell_length * scope});

                        PhysicalObject::Type t =
                            p_cell.getObjectPtr()->getType();

                        shape.setTexture(
                            physical_object_texture.getTexturePtr());

                        shape.setTextureRect(
                            physical_object_texture
                                [t][p_cell.getObjectPtr()->getPictureIndex()]);
                    }
                    else
                    {
                        shape.setPosition(player_position_window - difference);
                        shape.setFillColor(transparent);
                    }
                    Gui::getInstance()->m_window.draw(shape);
                }
            }
        }
    }
}

void
Gui::Graphic::display()
{
    Gui::getInstance()->m_window.clear();

    drawWorld();

    player_interface.drawInterface();

    if (inventory_interface.getStatus() == InventoryInterface::Status::OPEN)
    {
        Gui::getInstance()->graphic.inventory_interface.drawFullInventory();
    }
    else
    {
        Gui::getInstance()->graphic.inventory_interface.drawUsingCells();
    }

    Gui::getInstance()->m_window.display();
}

void
Gui::Graphic::zoom(float s)
{
    scope += s;
    if (scope > MAX_SCOPE) scope = MAX_SCOPE;
    if (scope < MIN_SCOPE) scope = MIN_SCOPE;

    player_interface.zoom();
    // std::cout << scope << "\n";
}

sf::Vector2f
Gui::Graphic::getPlayerPositionInWindow()
{
    return {Gui::getInstance()->getWindowCentre().x,
            Gui::getInstance()->getWindowCentre().y +
                player_interface.hero_shape.getSize().y * 0.5f};
}

float
Gui::Graphic::getScope()
{
    return scope;
}

sf::IntRect
Gui::Graphic::getCharTextureRect(char ch)
{
    return char_texture[ch][0];
}

const sf::Texture*
Gui::Graphic::getCharTexturePtr()
{
    return char_texture.getTexturePtr();
}