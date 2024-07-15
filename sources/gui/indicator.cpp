#include <exception>
#include <iostream>

#include "gui.hpp"

sf::Texture Gui::Graphic::Indicator::indicator_border_texture;

void
Gui::Graphic::Indicator::loadTexture()
{
    indicator_border_texture.loadFromFile(
        "C:/Users/arsbo/source/repos/game2/resources/"
        "player_info.png");
}

void
Gui::Graphic::Indicator::create()
{
    indicator_border_shape.setTexture(&indicator_border_texture);

    indicator_border_shape.setTextureRect(sf::IntRect(23, 20, 117, 51));

    procent_digit_shape_list.resize(4);

    for (int i = 0; i < procent_digit_shape_list.size(); ++i)
    {
        procent_digit_shape_list[i].setTexture(
            Gui::getInstance()->graphic.char_texture.getTexturePtr());
    }
}

void
Gui::Graphic::Indicator::draw()
{
    for (int i = 0; i < designation_letter_shape_list.size(); ++i)
    {
        Gui::getInstance()->m_window.draw(designation_letter_shape_list[i]);
    }
    Gui::getInstance()->m_window.draw(indicator_shape);
    Gui::getInstance()->m_window.draw(indicator_border_shape);

    for (int i = 0; i < str_procent.size(); ++i)
    {
        Gui::getInstance()->m_window.draw(procent_digit_shape_list[i]);
    }
}

void
Gui::Graphic::Indicator::setColor(const sf::Color& color)
{
    indicator_shape.setFillColor(color);
}

void
Gui::Graphic::Indicator::setSize(const sf::Vector2f& s2)
{
    sf::Vector2f s = s2;
    s.x -= designation.size(); // whitespaces

    m_size = s;

    float t1 = 0.4;
    float t2 = 0.4;
    float t3 = 0.2;

    for (int i = 0; i < designation_letter_shape_list.size(); ++i)
    {
        designation_letter_shape_list[i].setSize(
            {s.x * t1 / designation.size(), s.y});
    }

    indicator_border_shape.setSize({s.x * t2, s.y});
    indicator_shape.setSize({s.x * t2 * int_procent / 100 - 1, s.y - 1});

    for (int i = 0; i < str_procent.size(); ++i)
    {
        procent_digit_shape_list[i].setSize(
            {s.x * t3 / str_procent.size(), s.y});
    }
}

void
Gui::Graphic::Indicator::setPosition(const sf::Vector2f& p2)
{
    sf::Vector2f p = p2;

    for (int i = 0; i < designation.size(); ++i)
    {
        designation_letter_shape_list[i].setPosition({p.x, p.y});
        p.x += designation_letter_shape_list[i].getSize().x + 1;
    }

    indicator_border_shape.setPosition(p.x, p.y);
    indicator_shape.setPosition({p.x + 1, p.y + 1});

    for (int i = 0; i < procent_digit_shape_list.size(); ++i)
    {
        procent_digit_shape_list[i].setPosition(
            {1 + indicator_border_shape.getSize().x + p.x +
                 procent_digit_shape_list[i].getSize().x * i,
             p.y});
        p.x += 1;
    }
}

void
Gui::Graphic::Indicator::setDesignation(const std::string& str)
{
    designation = str;
    designation_letter_shape_list.resize(str.size());

    for (int i = 0; i < designation_letter_shape_list.size(); ++i)
    {
        designation_letter_shape_list[i].setTexture(
            Gui::getInstance()->graphic.char_texture.getTexturePtr());

        // std::cout << str[i] << '\n';

        // std::cout << Gui::getInstance()->graphic.char_texture[str[i]].size()
        //           << '\n';

        designation_letter_shape_list[i].setTextureRect(
            Gui::getInstance()->graphic.char_texture[std::tolower(str[i])][0]);
    }
    setSize(m_size);
}

void
Gui::Graphic::Indicator::setProcent(int procent)
{
    try
    {
        if (procent < 0 || procent > 100)
        {
            throw std::exception("Procent should be in diaposon [0;100]");
        }
        int_procent = procent;
        str_procent = std::to_string(procent) + '%';

        for (int i = 0; i < str_procent.size() - 1; ++i)
        {
            procent_digit_shape_list[i].setTextureRect(
                Gui::getInstance()->graphic.char_texture[str_procent[i]][0]);
        }

        procent_digit_shape_list[str_procent.size() - 1].setTextureRect(
            Gui::getInstance()->graphic.char_texture['%'][0]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    setSize(m_size);
}
