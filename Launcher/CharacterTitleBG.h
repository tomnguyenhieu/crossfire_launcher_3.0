#pragma once
#include <SFML/Graphics.hpp>

class CharacterTitleBG {
public:
    CharacterTitleBG(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
