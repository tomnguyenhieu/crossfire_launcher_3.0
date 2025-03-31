#include "LeftPanel.h"

LeftPanel::LeftPanel(sf::Texture& texture, const sf::Vector2f& position)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void LeftPanel::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect LeftPanel::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void LeftPanel::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}