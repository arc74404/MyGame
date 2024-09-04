#include "gui.hpp"
#include "text_button.hpp"
#include "texture_storage.hpp"
Gui::Graphic::MainMenu::MainMenu() : Menu(Menu::Type::MAIN)
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
Gui::Graphic::MainMenu::create()
{
    background.setTexture(
        &TextureStorage::getInstance()->main_menu_background_texture);
    background.setSize(Gui::getInstance()->getWindowSize());

    // std::shared_ptr<BaseButton> b;

    int button_count = 2;

    sf::Vector2f window_size = Gui::getInstance()->getWindowSize();
    // sf::Vector2f window_centre_size = Gui::getInstance()->getWindowCentre();
    sf::Vector2f button_size = {window_size.x * 0.4f,
                                window_size.y / button_count * 0.8f};
    float skip_y =
        (window_size.y - button_size.y * button_count) / (button_count + 1);

    games_button.setTexture(
        TextureStorage::getInstance()->games_button_texture.getTexturePtr());
    games_button.setTextureRect(
        TextureStorage::getInstance()
            ->games_button_texture[BaseButton::Status::NOT_SHINE][0]);
    games_button.setSize(button_size);
    games_button.setPosition({window_size.x * 0.05f, skip_y});
    // addButton(std::make_shared<RectangleButton>(games_button));

    // RectangleButton settings_button;
    // settings_button.setTexture(
    //     TextureStorage::getInstance()->settings_button_texture.getTexturePtr());
    // settings_button.setTextureRect(
    //     TextureStorage::getInstance()
    //         ->settings_button_texture[BaseButton::Status::NOT_SHINE][0]);
    // settings_button.setSize(button_size);
    // settings_button.setPosition({window_size.x * 0.05f, skip_y});
    // addButton(std::make_shared<RectangleButton>(settings_button));

    // for (int i = 0; i < button_count; ++i)
    // {
    // }
}

void
Gui::Graphic::MainMenu::update()
{
    static isDefaultButtonClickedOff is_games_clicked_off(&games_button,
                                                          sf::Mouse::Left);
    is_games_clicked_off.update();

    games_button.update();
    games_button.setTextureRect(
        TextureStorage::getInstance()
            ->games_button_texture[games_button.getStatus()][0]);

    if (is_games_clicked_off())
    {
        Gui::getInstance()->graphic.games_menu.open();
        // games_menu.open();
    }

    // for (int i = 0; i < button_vector.size(); ++i)
    // {
    //     button_vector[i]->update();
    //     button_vector[i]->setTextureRect(
    //         TextureStorage::getInstance()
    //             ->games_button_texture[button_vector[i]->getStatus()][0]);
    // }
}

void
Gui::Graphic::MainMenu::draw()
{
    Menu::draw();

    games_button.draw();
}