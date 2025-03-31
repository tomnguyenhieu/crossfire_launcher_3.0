#include "TeamLobbyDisplaySelect.h"

TeamLobbyDisplaySelect::TeamLobbyDisplaySelect(sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(position);
}

void TeamLobbyDisplaySelect::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect TeamLobbyDisplaySelect::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void TeamLobbyDisplaySelect::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void TeamLobbyDisplaySelect::setPosision(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}

sf::Vector2f TeamLobbyDisplaySelect::getPosition() const {
    return sprite.getPosition();
}
