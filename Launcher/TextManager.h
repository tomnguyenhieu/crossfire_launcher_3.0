#pragma once
#include <SFML/Graphics.hpp>

class TextManager
{
private:
	sf::Font font;
	sf::Text text;
public:
	TextManager(const sf::Font& font, const std::string& title, const int size, const sf::Color& color, const sf::Vector2f& position);
	void draw(sf::RenderWindow& window);
};

