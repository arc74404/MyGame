#include "gui.hpp"
#include "texture_storage.hpp"
Gui::Graphic::GamesMenu::WorldLaunchInterface::WorldLaunchInterface()
{
    world_name.setTexture(
        TextureStorage::getInstance()->text_button_texture.getTexturePtr());
    world_name.setTextureRect(
        TextureStorage::getInstance()
            ->text_button_texture[BaseButton::Status::NOT_SHINE][0]);

    rename_button.setTexture(
        TextureStorage::getInstance()->rename_button_texture.getTexturePtr());

    rename_button.setTextureRect(
        TextureStorage::getInstance()
            ->rename_button_texture[BaseButton::Status::NOT_SHINE][0]);
}
void
Gui::Graphic::GamesMenu::WorldLaunchInterface::draw()
{
    world_name.draw();
    rename_button.draw();
    run_button.draw();
}

sf::Vector2f
Gui::Graphic::GamesMenu::WorldLaunchInterface::getPosition()
{
    return world_name.getPosition();
}

void
Gui::Graphic::GamesMenu::WorldLaunchInterface::setSize(const sf::Vector2f& s)
{
    float x1 = 0.6f;
    float x2 = 0.2f;
    float x3 = 0.2f;

    world_name.setSize({s.x * x1, s.y});
    rename_button.setSize({s.x * x2, s.y});
    run_button.setSize({s.x * x3, s.y});

    setPosition(getPosition());
}

void
Gui::Graphic::GamesMenu::WorldLaunchInterface::setPosition(
    const sf::Vector2f& p)
{
    world_name.setPosition(p);

    rename_button.setPosition({p.x + world_name.getSize().x, p.y});

    run_button.setPosition(
        {p.x + world_name.getSize().x + rename_button.getSize().x, p.y});
}