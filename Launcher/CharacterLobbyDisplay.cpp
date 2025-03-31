#include "CharacterLobbyDisplay.h"

CharacterLobbyDisplay::CharacterLobbyDisplay(sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(position);
}

void CharacterLobbyDisplay::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void CharacterLobbyDisplay::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}