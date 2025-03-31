#pragma once
#include <SFML/Graphics.hpp>

class CharacterLobbyDisplay {
public:
    CharacterLobbyDisplay(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

