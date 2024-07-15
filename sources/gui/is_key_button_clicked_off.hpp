#ifndef IS_KEY_BUTTON_CLICKED_OFF_HPP
#define IS_KEY_BUTTON_CLICKED_OFF_HPP

#include "base_button.hpp"

class isKeyboardButtonClickedOff
{
public:
    isKeyboardButtonClickedOff();

    void setKey(sf::Keyboard::Key k);

    bool operator()();

private:
    bool is_pressed;

    sf::Keyboard::Key m_key;
};

class isDefaultButtonClickedOff
{
public:
    isDefaultButtonClickedOff(const BaseButton* b);

    bool operator()();

private:
    bool is_pressed;

    const BaseButton* m_button;
};
#endif // !IS_KEY_BUTTON_CLICKED_OFF_HPP