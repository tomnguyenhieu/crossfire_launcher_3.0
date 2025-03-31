#include "RightPanel.h"

RightPanel::RightPanel(sf::Texture& texture, const sf::Vector2f& position)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void RightPanel::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect RightPanel::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void RightPanel::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}