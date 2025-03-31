#pragma once
#include <SFML/Graphics.hpp>

class TeamLobbyDisplaySelect {
public:
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;

    TeamLobbyDisplaySelect(sf::Texture& texture, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);
    void setPosision(const sf::Vector2f& position);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

