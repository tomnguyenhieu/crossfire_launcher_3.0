#pragma once
#include <SFML/Graphics.hpp>

class LoginPage
{
private:
    sf::Sprite sprite;

public:
    sf::Texture texture;
    sf::FloatRect getGlobalBounds() const;
    LoginPage(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);
};

