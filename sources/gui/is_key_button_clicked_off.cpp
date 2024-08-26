#include "is_key_button_clicked_off.hpp"

#include <iostream>

#include "gui.hpp"

isKeyboardButtonClickedOff::isKeyboardButtonClickedOff() : is_pressed(false)
{
}

isKeyboardButtonClickedOff::isKeyboardButtonClickedOff(sf::Keyboard::Key k)
    : isKeyboardButtonClickedOff()
{
    setKey(k);
}

void
isKeyboardButtonClickedOff::update()
{
    if (sf::Keyboard::isKeyPressed(m_key))
    {
        is_pressed = true;

        is_clicked_off = false;
    }
    else
    {
        if (is_pressed) is_clicked_off = true;
        else is_clicked_off = false;

        is_pressed = false;
    }
}

bool
isKeyboardButtonClickedOff::operator()()
{
    return is_clicked_off;
}

void
isKeyboardButtonClickedOff::setKey(sf::Keyboard::Key k)
{
    m_key = k;
}

//////////////////////////////////////////////////////////

isMouseButtonClickedOff::isMouseButtonClickedOff() : is_pressed(false)
{
}

isMouseButtonClickedOff::isMouseButtonClickedOff(sf::Mouse::Button b)
    : isMouseButtonClickedOff()
{
    setMouseButton(b);
}

void
isMouseButtonClickedOff::update()
{
    if (sf::Mouse::isButtonPressed(m_button))
    {
        is_pressed = true;

        is_clicked_off = false;
    }
    else
    {
        if (is_pressed) is_clicked_off = true;
        else is_clicked_off = false;

        is_pressed = false;
    }
}

bool
isMouseButtonClickedOff::operator()()
{
    return is_clicked_off;
}

void
isMouseButtonClickedOff::setMouseButton(sf::Mouse::Button b)
{
    m_button = b;
}

//////////////////////////////////////////////////////////
isDefaultButtonClickedOff::isDefaultButtonClickedOff()
{
    // m_button            = NULL;
    is_key_button_exist = false;
}

isDefaultButtonClickedOff::isDefaultButtonClickedOff(const BaseButton* b,
                                                     sf::Mouse::Button mb)
{
    m_button = b;

    mouse_button        = mb;
    is_key_button_exist = false;
}
isDefaultButtonClickedOff::isDefaultButtonClickedOff(const BaseButton* b,
                                                     sf::Mouse::Button mb,
                                                     sf::Keyboard::Key k)
{
    m_button            = b;
    mouse_button        = mb;
    is_key_button_exist = true;
    key_button          = k;
}

void
isDefaultButtonClickedOff::update()
{
    sf::Vector2f mouse_position = Gui::getInstance()->getMousePosition();

    // std::cout << m_button << '\n';

    bool is_in_shape =
        static_cast<const RectangleButton*>(m_button)->isPointInButton(
            mouse_position);

    bool is_pressing =
        sf::Mouse::isButtonPressed(mouse_button) &&
        (!is_key_button_exist || sf::Keyboard::isKeyPressed(key_button));

    if (is_in_shape)
    {
        if (is_pressing)
        {
            is_pressed = true;

            is_clicked_off = false;
        }
        else
        {
            if (is_pressed)
            {
                is_pressed = false;

                is_clicked_off = true;
            }
            else
            {
                is_pressed = false;

                is_clicked_off = false;
            }
        }
    }
    else
    {
        if (is_pressing)
        {
            is_pressed = true;
        }
        else
        {
            is_pressed = false;
        }
        is_clicked_off = false;
    }
}

bool
isDefaultButtonClickedOff::operator()()
{
    return is_clicked_off;
}

void
isDefaultButtonClickedOff::setButton(const BaseButton* b)
{
    m_button = b;
}

void
isDefaultButtonClickedOff::setMouseButtonChecking(sf::Mouse::Button b)
{
    mouse_button = b;
}

void
isDefaultButtonClickedOff::setKeyButtonChecking(sf::Keyboard::Key k)
{
    key_button = k;

    is_key_button_exist = true;
}
