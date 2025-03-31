#pragma once
#include <SFML/Graphics.hpp>

class BackgroundManager {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    BackgroundManager(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
};
