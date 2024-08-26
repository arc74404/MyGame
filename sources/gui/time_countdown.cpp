#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "gui/gui.hpp"

#include "texture_storage.hpp"

// void
// Gui::Graphic::TimeCountdown::loadTexture()
// {

// }

void
Gui::Graphic::TimeCountdown::create()
{
    indicator_border_shape.setTexture(
        &TextureStorage::getInstance()->indicator_border_texture);

    indicator_border_shape.setTextureRect(sf::IntRect(23, 20, 117, 51));

    seconds_digit_shape_list.resize(8); // 999.99 s

    for (int i = 0; i < seconds_digit_shape_list.size(); ++i)
    {
        seconds_digit_shape_list[i].setTexture(
            TextureStorage::getInstance()->char_texture.getTexturePtr());
    }
}

void
Gui::Graphic::TimeCountdown::draw()
{
    Gui::getInstance()->m_window.draw(indicator_shape);
    Gui::getInstance()->m_window.draw(indicator_border_shape);

    for (int i = 0; i < seconds_digit_shape_list.size(); ++i)
    {
        Gui::getInstance()->m_window.draw(seconds_digit_shape_list[i]);
    }
}

void
Gui::Graphic::TimeCountdown::setColor(const sf::Color& color)
{
    indicator_shape.setFillColor(color);
}

void
Gui::Graphic::TimeCountdown::setSize(const sf::Vector2f& s2)
{
    sf::Vector2f s = s2;
    s.x -= seconds_digit_shape_list.size(); // whitespaces

    m_size = s2;

    float t1 = 0.8;
    float t2 = 0.2;

    indicator_border_shape.setSize({s.x * t1, s.y});
    indicator_shape.setSize({s.x * t1 * left_seconds / full_time, s.y - 1});

    for (int i = 0; i < str_left_seconds.size(); ++i)
    {
        seconds_digit_shape_list[i].setSize(
            {s.x * t2 / str_left_seconds.size(), s.y});
    }
}

void
Gui::Graphic::TimeCountdown::setPosition(const sf::Vector2f& p2)
{
    sf::Vector2f p = p2;

    m_position = p2;

    indicator_border_shape.setPosition(p.x, p.y);
    indicator_shape.setPosition({p.x + 1, p.y + 1});

    for (int i = 0; i < seconds_digit_shape_list.size(); ++i)
    {
        seconds_digit_shape_list[i].setPosition(
            {1 + indicator_border_shape.getSize().x + p.x +
                 seconds_digit_shape_list[i].getSize().x * i,
             p.y});
        p.x += 1;
    }
}

void
Gui::Graphic::TimeCountdown::setSeconds(float s)
{
    try
    {
        if (s < 0 || s >= 1000)
        {
            throw std::exception("Seconds should be in diaposon [0;999]");
        }
        left_seconds = s;

        std::ostringstream stream;

        stream << std::fixed << std::setprecision(2)
               << s; // указываем два символа после точки

        str_left_seconds = stream.str() + " s";

        // std::cout << str_seconds << '\n';

        for (int i = 0; i < str_left_seconds.size() - 2; ++i)
        {
            seconds_digit_shape_list[i].setTextureRect(
                TextureStorage::getInstance()
                    ->char_texture[str_left_seconds[i]][0]);
        }
        seconds_digit_shape_list[str_left_seconds.size() - 2].setTextureRect(
            TextureStorage::getInstance()->char_texture[' '][0]);

        seconds_digit_shape_list[str_left_seconds.size() - 1].setTextureRect(
            TextureStorage::getInstance()->char_texture['s'][0]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    setSize(m_size);
    setPosition(m_position);
}
void
Gui::Graphic::TimeCountdown::setFullTime(float ft)
{
    full_time = ft;
}
