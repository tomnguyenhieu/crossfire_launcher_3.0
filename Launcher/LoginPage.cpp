#include "LoginPage.h"

LoginPage::LoginPage(sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void LoginPage::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect LoginPage::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void LoginPage::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}
