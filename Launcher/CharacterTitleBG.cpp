#include "CharacterTitleBG.h"

CharacterTitleBG::CharacterTitleBG(sf::Texture& texture, const sf::Vector2f& position) {

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(position);
}

void CharacterTitleBG::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}