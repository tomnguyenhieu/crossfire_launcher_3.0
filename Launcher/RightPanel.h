#pragma once
#include <SFML/Graphics.hpp>

class RightPanel
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    sf::FloatRect getGlobalBounds() const;
    RightPanel(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);
};

