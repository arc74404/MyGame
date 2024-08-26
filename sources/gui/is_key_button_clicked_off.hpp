#ifndef IS_KEY_BUTTON_CLICKED_OFF_HPP
#define IS_KEY_BUTTON_CLICKED_OFF_HPP

#include "base_button.hpp"

class isKeyboardButtonClickedOff
{
public:
    isKeyboardButtonClickedOff();

    isKeyboardButtonClickedOff(sf::Keyboard::Key k);

    void update();

    void setKey(sf::Keyboard::Key k);

    bool operator()();

private:
    bool is_pressed;

    bool is_clicked_off;

    sf::Keyboard::Key m_key;
};

class isMouseButtonClickedOff
{
public:
    isMouseButtonClickedOff();

    isMouseButtonClickedOff(sf::Mouse::Button);

    void update();

    void setMouseButton(sf::Mouse::Button);

    bool operator()();

private:
    bool is_pressed;

    bool is_clicked_off;

    sf::Mouse::Button m_button;
};

class isDefaultButtonClickedOff
{
public:
    isDefaultButtonClickedOff();

    isDefaultButtonClickedOff(const BaseButton* b, sf::Mouse::Button mb);

    isDefaultButtonClickedOff(const BaseButton* b, sf::Mouse::Button mb,
                              sf::Keyboard::Key k);

    void setButton(const BaseButton* b);
    void setMouseButtonChecking(sf::Mouse::Button b);
    void setKeyButtonChecking(sf::Keyboard::Key k);

    void update();

    bool operator()();

private:
    bool is_pressed;

    bool is_clicked_off;

    const BaseButton* m_button;

    sf::Mouse::Button mouse_button;

    bool is_key_button_exist;
    sf::Keyboard::Key key_button;
};
#endif // !IS_KEY_BUTTON_CLICKED_OFF_HPP