#include "gui.hpp"

Gui::Graphic::Menu::Type Gui::Graphic::Menu::open_menu_type =
    Gui::Graphic::Menu::Type::NONE;

Gui::Graphic::Menu::Menu(Type t)
{
    m_type = t;
}


// void
// Gui::Graphic::Menu::addButton(const std::shared_ptr<BaseButton>& b)
// {
//     button_vector.emplace_back(b);
// }
void
Gui::Graphic::Menu::open()
{
    open_menu_type = m_type;
}
void
Gui::Graphic::Menu::draw()
{
    Gui::getInstance()->m_window.draw(background);

    // for (int i = 0; i < button_vector.size(); ++i)
    // {
    //     button_vector[i]->draw();
    // }
}

Gui::Graphic::Menu::Type
Gui::Graphic::Menu::getOpenMenuType()
{
    return open_menu_type;
}
