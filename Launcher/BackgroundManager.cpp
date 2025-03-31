#include "BackgroundManager.h"

BackgroundManager::BackgroundManager(sf::Texture& texture, const sf::Vector2f& position) {
    
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void BackgroundManager::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
