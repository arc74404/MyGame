#ifndef MY_TEXTURE_HPP
#define MY_TEXTURE_HPP

#include <SFML/Graphics.hpp>

#include <map>

template <typename S> class MyTexture
{
public:
    MyTexture();

    void loadFromFile(const std::string& filename);

    const sf::Texture* getTexturePtr() const;

    std::vector<sf::IntRect>& operator[](S m_key);

    // void insert(S m_key, int index, const sf::IntRect& value);

private:
    sf::Texture m_texture;

    std::map<S, std::vector<sf::IntRect>> tetxure_rect_map;
};

//////////////////////////////////////

template <typename S> MyTexture<S>::MyTexture()
{
}

template <typename S>
void
MyTexture<S>::loadFromFile(const std::string& filename)
{
    m_texture.loadFromFile(filename);
}

template <typename S>
const sf::Texture*
MyTexture<S>::getTexturePtr() const
{
    return &m_texture;
}

template <typename S>
std::vector<sf::IntRect>&
MyTexture<S>::operator[](S m_key)
{
    return tetxure_rect_map[m_key];
}

// template <typename S>
// void
// MyTexture<S>::insert(S m_key, int index, const sf::IntRect& value)
// {
//     tetxure_rect_map[m_key][index] = value;
// }

#endif // !MY_TEXTURE_HPP