#include "Logo.h"

Logo::Logo(sf::Texture& texture, const sf::Vector2f& position)
    : currentFrameX(0), currentFrameY(0), frameWidth(1848 / 7), frameHeight(630 / 7), totalFramesX(7), totalFramesY(7),
    timeSinceLastUpdate(0.0f), frameTime(0.05f)
{
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(0.8, 0.8));
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void Logo::update(float deltaTime) {
    timeSinceLastUpdate += deltaTime;

    if (timeSinceLastUpdate >= frameTime) { 
        timeSinceLastUpdate -= frameTime; 

        currentFrameX++;
        if (currentFrameX >= totalFramesX) {
            currentFrameX = 0;
            currentFrameY++;
            if (currentFrameY >= totalFramesY) {
                currentFrameY = 0;
            }
        }
        sprite.setTextureRect(sf::IntRect(
            currentFrameX * frameWidth,
            currentFrameY * frameHeight,
            frameWidth,
            frameHeight
        ));
    }
}

void Logo::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}