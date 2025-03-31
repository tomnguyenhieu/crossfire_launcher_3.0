#pragma once
#include <SFML/Graphics.hpp>

class Logo
{
public:
	Logo(sf::Texture& texture, const sf::Vector2f& position);
	void draw(sf::RenderWindow& window);
	void update(float deltaTime);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock;
	int currentFrameX;
	int currentFrameY;
	const int frameWidth;
	const int frameHeight;
	const int totalFramesX;
	const int totalFramesY;
	float timeSinceLastUpdate;
	const float frameTime;
};
