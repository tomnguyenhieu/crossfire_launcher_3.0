#include "TopMenu.h"

TopMenu::TopMenu(sf::Texture& texture, const sf::Vector2f& position)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void TopMenu::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect TopMenu::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void TopMenu::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}