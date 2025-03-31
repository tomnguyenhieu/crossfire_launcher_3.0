#pragma once
#include <SFML/Graphics.hpp>

class TopMenu
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    sf::FloatRect getGlobalBounds() const;
    TopMenu(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);
};

