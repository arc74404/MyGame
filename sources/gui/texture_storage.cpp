#include "texture_storage.hpp"

TextureStorage::TextureStorage()
{
}

TextureStorage*
TextureStorage::getInstance()
{
    static TextureStorage texture_storage;
    return &texture_storage;
}

void
TextureStorage::loadObjectTexture()
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
        TextureStorage::getInstance()
            ->physical_object_texture[PhysicalObject::Type::BUSH_BLUEBERRY]
            .emplace_back(sf::IntRect(12 + 71 * i, 81, 70, 63));
        TextureStorage::getInstance()
            ->physical_object_texture[PhysicalObject::Type::BUSH_STRAWBERRY]
            .emplace_back(sf::IntRect(12 + 71 * i, 150, 70, 63));
    }
}

void
TextureStorage::loadCharTexture()
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
    int_rect.left += 8;
    char_texture[' '].emplace_back(int_rect);
}

void
TextureStorage::loadInventoryInterfaceTextures()
{
    inventory_cell_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/cell_storage_texture.png");

    sf::IntRect r = {42, 58, 73, 67};
    inventory_cell_texture[BaseButton::Status::NOT_SHINE].emplace_back(r);

    r.left += 90;
    inventory_cell_texture[BaseButton::Status::HIGHLIGHTED].emplace_back(r);

    r.left += 90;
    inventory_cell_texture[BaseButton::Status::SHINE].emplace_back(r);

    storage_objects_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/inventory_objects.png");

    r = {40, 165, 110, 110};

    storage_objects_texture[StorageObject::Type::AXE].emplace_back(r);

    r.left += 123;
    storage_objects_texture[StorageObject::Type::AXE].emplace_back(r);

    r.left += 126;
    storage_objects_texture[StorageObject::Type::AXE].emplace_back(r);

    r = {38, 17, 120, 123};
    storage_objects_texture[StorageObject::Type::PICKAXE].emplace_back(r);

    r.left += 123;
    storage_objects_texture[StorageObject::Type::PICKAXE].emplace_back(r);

    r.left += 123;
    storage_objects_texture[StorageObject::Type::PICKAXE].emplace_back(r);

    r.left = 30;
    r.top += 300;

    storage_objects_texture[StorageObject::Type::WOOD].emplace_back(r);

    r.left += 123;

    r.width -= 20;
    r.height -= 20;

    storage_objects_texture[StorageObject::Type::STONE].emplace_back(r);

    r.left += 95;
    r.width -= 25;

    storage_objects_texture[StorageObject::Type::STRAWBERRY].emplace_back(r);

    r.width += 20;
    r.left += 65;

    storage_objects_texture[StorageObject::Type::BLUEBERRY].emplace_back(r);

    r.left += 100;

    storage_objects_texture[StorageObject::Type::APPLE].emplace_back(r);

    storage_objects_texture[StorageObject::Type::HAND].emplace_back(
        sf::IntRect(0, 0, 0, 0));
}

void
TextureStorage::loadTimeCountdownTexture()
{
    indicator_border_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/"
        "player_info.png");
}
void
TextureStorage::loadIndicatorTexture()
{
    indicator_border_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/"
        "player_info.png");
}

void
TextureStorage::loadPlayerInterfaceTextures()
{
    float cell_length = WorldCell::getLength();

    hero_texture.loadFromFile("C:/Users/arsbo/source/repos/game2/"
                              "resources/hero.png");

    sf::Vector2i texture_rect_size = {17, 31};
    sf::Vector2i texture_rect_pos  = {10, 2};

    hero_texture[Player::Status::STAND].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size));

    texture_rect_size = {20, 31};

    texture_rect_pos.x += 34;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 0

    texture_rect_pos.x += 36;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 1

    texture_rect_pos.x += 34;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 2

    texture_rect_pos.x += 36;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 3

    texture_rect_pos.x += 36;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 4

    texture_rect_pos.x += 34;
    hero_texture[Player::Status::WALK].emplace_back(
        sf::IntRect(texture_rect_pos, texture_rect_size)); // 5
}

void
TextureStorage::loadButtonTextures()
{
    arrow_button_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/arrow_button.png");

    sf::IntRect r = {27, 11, 88, 116};

    sf::IntRect reverse_int_rect;

    arrow_button_texture[BaseButton::Status::NOT_SHINE].emplace_back(r);
    reverse_int_rect = r;
    reverse_int_rect.top += reverse_int_rect.height;
    reverse_int_rect.height *= -1;
    arrow_button_texture[BaseButton::Status::NOT_SHINE].emplace_back(
        reverse_int_rect);

    r.left += 103;
    arrow_button_texture[BaseButton::Status::HIGHLIGHTED].emplace_back(r);
    reverse_int_rect = r;
    reverse_int_rect.top += reverse_int_rect.height;
    reverse_int_rect.height *= -1;
    arrow_button_texture[BaseButton::Status::HIGHLIGHTED].emplace_back(
        reverse_int_rect);

    r.left += 104;
    arrow_button_texture[BaseButton::Status::SHINE].emplace_back(r);
    reverse_int_rect = r;
    reverse_int_rect.top += reverse_int_rect.height;
    reverse_int_rect.height *= -1;
    arrow_button_texture[BaseButton::Status::SHINE].emplace_back(
        reverse_int_rect);
}

void
TextureStorage::loadAllTextures()
{
    loadObjectTexture();
    loadCharTexture();
    loadInventoryInterfaceTextures();
    loadTimeCountdownTexture();
    loadIndicatorTexture();
    loadPlayerInterfaceTextures();
    loadButtonTextures();
}