#include "TextManager.h"

TextManager::TextManager(const sf::Font& font, const std::string& title, const int size, const sf::Color& color, const sf::Vector2f& position)
{
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(size);
    text.setFillColor(color);
    //text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(position);
}

void TextManager::draw(sf::RenderWindow& window)
{
	window.draw(text);
}
