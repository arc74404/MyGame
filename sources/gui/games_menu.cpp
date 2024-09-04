#include "gui.hpp"
#include "text_button.hpp"
#include "texture_storage.hpp"

Gui::Graphic::GamesMenu::GamesMenu() : Menu(Menu::Type::MAIN)
{
}
// std::shared_ptr<BaseButton> b;

// TextButton text_button;
// text_button.setTexture(
//     TextureStorage::getInstance()->text_button_texture.getTexturePtr());
// text_button.setTextureRect(
//     TextureStorage::getInstance()
//         ->text_button_texture[BaseButton::Status::NOT_SHINE][0]);

// int button_count = 5;

// sf::Vector2f window_size        = Gui::getInstance()->getWindowSize();
// sf::Vector2f window_centre_size = Gui::getInstance()->getWindowCentre();
// sf::Vector2f text_button_size   = {window_size.x * 0.4f,
//                                    window_size.y / button_count * 0.8f};

// text_button.setSize(text_button_size);

// float skip_y = (window_size.y - text_button_size.y * button_count) /
//                (button_count + 1);

// for (int i = 0; i < button_count; ++i)
// {
//     text_button.setPosition(
//         {window_centre_size.x - text_button_size.x * 0.5f,
//          (i + 1) * skip_y + i * text_button_size.y});

//     // text_button.setText("abcdefghimfsgsr");

//     addButton(std::make_shared<TextButton>(text_button));
// }
void
Gui::Graphic::GamesMenu::create()
{
    background.setTexture(
        &TextureStorage::getInstance()->main_menu_background_texture);
    background.setSize(Gui::getInstance()->getWindowSize());

    int button_count = 5;

    sf::Vector2f window_size        = Gui::getInstance()->getWindowSize();
    sf::Vector2f window_centre_size = Gui::getInstance()->getWindowCentre();
    sf::Vector2f button_size        = {window_size.x * 0.4f,
                                       window_size.y / button_count * 0.8f};

    world_launch_interface_list.resize(button_count);

    float skip_y =
        (window_size.y - button_size.y * button_count) / (button_count + 1);

    for (int i = 0; i < world_launch_interface_list.size(); ++i)
    {
        world_launch_interface_list[i].setPosition(
            {window_centre_size.x - button_size.x * 0.5f,
             (i + 1) * skip_y + i * button_size.y});
        world_launch_interface_list[i].setSize(button_size);
    }
}

void
Gui::Graphic::GamesMenu::update()
{
}

void
Gui::Graphic::GamesMenu::draw()
{
    Menu::draw();

    for (int i = 0; i < world_launch_interface_list.size(); ++i)
    {
        world_launch_interface_list[i].draw();
    }

    // games_button.draw();
}