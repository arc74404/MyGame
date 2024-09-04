#include "text_button.hpp"

#include <iostream>

#include "gui/gui.hpp"

#include "texture_storage.hpp"

const int TextButton::MAX_TEXT_LENGTH = 15;

TextButton::TextButton()
{
}

void
TextButton::setPosition(const sf::Vector2f& position)
{
    BaseButton::setPosition(position);

    float skip = (getSize().x - letter_shape_size.x * MAX_TEXT_LENGTH) /
                 (MAX_TEXT_LENGTH + 1);

    float y =
        (shape.getSize().y - letter_shape_size.y) * 0.5 + shape.getPosition().y;

    // std::cout << skip << '\n';

    for (int i = 0; i < letter_shape_vector.size(); ++i)
    {
        letter_shape_vector[i].setPosition(
            {position.x + letter_shape_size.x * i + (skip) * (i + 1), y});
    }
}

void
TextButton::setSize(const sf::Vector2f& size)
{
    RectangleButton::setSize(size);

    letter_shape_size = {(size.x / MAX_TEXT_LENGTH * 0.8f), size.y * 0.8f};

    for (int i = 0; i < letter_shape_vector.size(); ++i)
    {
        letter_shape_vector[i].setSize(letter_shape_size);
    }
    setPosition(getPosition());
}

void
TextButton::setText(const std::string& text)
{
    try
    {
        if (text.size() > MAX_TEXT_LENGTH)
        {
            // std::cout << text.size() << '\n';
            throw std::exception("text size is too big");
        }
        letter_shape_vector.resize(text.size());

        for (int i = 0; i < letter_shape_vector.size(); ++i)
        {
            letter_shape_vector[i].setTexture(
                TextureStorage::getInstance()->char_texture.getTexturePtr());

            letter_shape_vector[i].setTextureRect(
                TextureStorage::getInstance()->char_texture[text[i]][0]);
        }

        setSize(getSize());
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void
TextButton::draw() const
{
    BaseButton::draw();

    for (int i = 0; i < letter_shape_vector.size(); ++i)
    {
        letter_shape_vector[i].draw();
    }
}