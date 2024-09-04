#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include "gui/rectangle_button.hpp"

class TextButton : public RectangleButton
{
public:
    static const int MAX_TEXT_LENGTH;

    TextButton();

    void setText(const std::string& setText);

    void setSize(const sf::Vector2f& s);

    void setPosition(const sf::Vector2f& pos);

    void draw() const override;

private:
    std::string m_text;

    std::vector<RectangleButton> letter_shape_vector;

    sf::Vector2f letter_shape_size;
};

#endif // !TEXT_BUTTON_HPP