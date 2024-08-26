
#include <iostream>

#include "app/app.hpp"
#include "player/player.hpp"
#include "world/cell.hpp"
#include "world/location.hpp"
#include "world/world.hpp"

#include "gui.hpp"
#include "texture_storage.hpp"

Gui::Graphic::Graphic()
{
    rendering_radius = 4;
}

// void
// Gui::Graphic::loadObjectTexture()
// {

// }

// void
// Gui::Graphic::loadCharTexture()
// {

// }

// void
// Gui::Graphic::loadTextures()
// {
//     Gui::Graphic::Indicator::loadTexture();
//     Gui::Graphic::TimeCountdown::loadTexture();
//     Gui::Graphic::InventoryInterface::loadTexture();

//     loadCharTexture();

//     player_interface.create();

//     inventory_interface.create();

//     loadObjectTexture();

//     zoom(2.5f);
// }

void
Gui::Graphic::drawWorld()
{

    static sf::Color transparent(0, 0, 0, 0);
    sf::Vector2f player_position = Player::getInstance()->getPosition();

    int cell_length = WorldCell::getLength();

    float dropped_object_length = DroppedObject::getLength();

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

    static int hh = 0;
    hh++;

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

                const Location& location =
                    World::getInstance()->getLocation(w_x, w_y);

                for (int l_x = 0; l_x < location_cell_length; ++l_x)
                {
                    if (player_line_y == l_y &&
                        w_x ==
                            player_location_coordinate.x + rendering_radius &&
                        w_y == player_location_coordinate.y &&
                        l_x == location_cell_length - 1)
                    {
                        player_interface.drawPlayer();
                    }

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

                    if (p_cell.isMain() && !p_cell.isEmpty())
                    {
                        sf::RectangleShape shape;

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

                        // if (Gui::getInstance()->isMouseInRectangle(
                        //         shape.getPosition(), shape.getSize()))
                        // {
                        //     shape.setOutlineColor(sf::Color::Red);
                        //     shape.setOutlineThickness(3);
                        // }

                        shape.setTexture(
                            TextureStorage::getInstance()
                                ->physical_object_texture.getTexturePtr());

                        shape.setTextureRect(
                            TextureStorage::getInstance()
                                ->physical_object_texture
                                    [t]
                                    [p_cell.getObjectPtr()->getPictureIndex()]);
                        Gui::getInstance()->m_window.draw(shape);
                    }
                    // else
                    // {
                    //     shape.setPosition(player_position_window -
                    //     difference); shape.setFillColor(transparent);
                    // }
                }
            }
        }
    }
    for (int w_y = player_location_coordinate.y - rendering_radius;
         w_y <= player_location_coordinate.y + rendering_radius; ++w_y)
    {
        for (int w_x = player_location_coordinate.x - rendering_radius;
             w_x <= player_location_coordinate.x + rendering_radius; ++w_x)
        {
            const Location& location =
                World::getInstance()->getLocation(w_x, w_y);
            const std::vector<std::shared_ptr<DroppedObject>>&
                dropped_object_vector = location.getDroppedObjectVector();

            for (int i = 0; i < dropped_object_vector.size(); ++i)
            {
                sf::RectangleShape shape;

                shape.setSize({dropped_object_length * scope,
                               dropped_object_length * scope});

                shape.setFillColor(sf::Color(255, 255, 255, 220));

                sf::Vector2f difference;

                difference.x = (player_position.x -
                                dropped_object_vector[i]->getPosition().x) *
                               scope;

                difference.y = (player_position.y -
                                dropped_object_vector[i]->getPosition().y) *
                               scope;

                shape.setPosition(player_position_window - difference);

                shape.setTexture(TextureStorage::getInstance()
                                     ->storage_objects_texture.getTexturePtr());

                std::shared_ptr<Resource> res_ptr =
                    std::reinterpret_pointer_cast<Resource>(
                        dropped_object_vector[i]);

                shape.setTextureRect(
                    TextureStorage::getInstance()
                        ->storage_objects_texture[res_ptr->getType()][0]);

                Gui::getInstance()->m_window.draw(shape);
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
        Gui::getInstance()->graphic.craft_menu_interface.draw();
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

void
Gui::Graphic::create()
{
    player_interface.create();
    inventory_interface.create();
    craft_menu_interface.create();

    zoom(2.5);
}