#ifndef TEXTURE_STORAGE_HPP
#define TEXTURE_STORAGE_HPP

#include "player/player.hpp"
#include "storage/instrument.hpp"
#include "storage/resource.hpp"

#include "my_texture.hpp"

struct TextureStorage
{
public:
    static TextureStorage* getInstance();

    void loadAllTextures();

    sf::Texture indicator_border_texture;

    sf::Texture main_menu_background_texture;

    //////////////////////////////////////////////
    MyTexture<BaseButton::Status> inventory_cell_texture;
    //////////////////////////////////////////////
    MyTexture<BaseButton::Status> arrow_button_texture;
    //////////////////////////////////////////////
    MyTexture<BaseButton::Status> text_button_texture;
    ///////////////////////////////////////////////
    MyTexture<BaseButton::Status> games_button_texture;
    ///////////////////////////////////////////////
    MyTexture<BaseButton::Status> rename_button_texture;
    ///////////////////////////////////////////////
    MyTexture<StorageObject::Type> storage_objects_texture;
    //////////////////////////////////////////////
    MyTexture<Player::Status> hero_texture;
    ///////////////////////////////////////////////
    MyTexture<PhysicalObject::Type> physical_object_texture;
    ////////////////////////////////////////////////
    MyTexture<char> char_texture;

private:
    TextureStorage();

    void loadObjectTexture();

    void loadCharTexture();

    void loadInventoryInterfaceTextures();

    void loadPlayerInterfaceTextures();

    void loadTimeCountdownTexture();

    void loadIndicatorTexture();

    void loadButtonTextures();
};

#endif // !TEXTURE_STORAGE_HPP