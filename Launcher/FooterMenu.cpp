#include "FooterMenu.h"

FooterMenu::FooterMenu(sf::Texture& texture, const sf::Vector2f& position)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void FooterMenu::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect FooterMenu::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void FooterMenu::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}