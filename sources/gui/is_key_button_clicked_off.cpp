#include "is_key_button_clicked_off.hpp"

#include "gui.hpp"

isKeyboardButtonClickedOff::isKeyboardButtonClickedOff() : is_pressed(false)
{
}

bool
isKeyboardButtonClickedOff::operator()()
{
    bool res;
    if (sf::Keyboard::isKeyPressed(m_key))
    {
        is_pressed = true;

        res = false;
    }
    else
    {
        if (is_pressed) res = true;
        else res = false;

        is_pressed = false;
    }
    return res;
}

void
isKeyboardButtonClickedOff::setKey(sf::Keyboard::Key k)
{
    m_key = k;
}

isDefaultButtonClickedOff::isDefaultButtonClickedOff(const BaseButton* b)
{
    m_button = b;
}

bool
isDefaultButtonClickedOff::operator()()
{
    bool res;
    sf::Vector2f mouse_position = Gui::getInstance()->getMousePosition();

    bool is_in_shape = m_button->isPointInButton(mouse_position);
    bool is_pressing = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (is_in_shape)
    {
        if (is_pressing)
        {
            is_pressed = true;

            res = false;
        }
        else
        {
            if (is_pressed)
            {
                is_pressed = false;

                res = true;
            }
            else
            {
                is_pressed = false;

                res = false;
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
        res = false;
    }
    return res;
}
