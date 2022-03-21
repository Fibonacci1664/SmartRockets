#include "Target.h"
#include <iostream>

Target::Target(sf::RenderWindow* hwnd) : window(hwnd)
{
    moonPosition = sf::Vector2f(640.0f, 100.0f);

    loadTexture();
	initTarget();
    initMoonDebug();
}

Target::~Target()
{

}

void Target::update(float dt)
{

}

void Target::render()
{
    window->draw(moonSprite);

    if (displayDebug)
    {
        window->draw(moonColliderVisualized);
    }
}

void Target::initTarget()
{
    moonTexture.setSmooth(true);
    moonSprite.setTexture(moonTexture);
    moonSize = moonTexture.getSize();
    moonSprite.setOrigin(moonSize.x * 0.5f, moonSize.y * 0.5f);
    moonSprite.setScale(0.1f, 0.1f);
    moonSprite.setPosition(moonPosition);
}

void Target::initMoonDebug()
{
    moonColliderVisualized.setFillColor(sf::Color(0, 0, 0, 0));
    moonColliderVisualized.setOutlineColor(sf::Color::Magenta);
    moonColliderVisualized.setOutlineThickness(1.0f);
    moonColliderVisualized.setRadius(14.0f);
    moonColliderVisualized.setOrigin(sf::Vector2f(14.0f, 14.0f));
    moonColliderVisualized.setPosition(sf::Vector2f(moonSprite.getPosition().x, moonSprite.getPosition().y));
}

void Target::loadTexture()
{
    if (!moonTexture.loadFromFile("res/sprites/AsteroidSprite.png"))
    {
        std::cout << "Error loading moon texture\n";
    }
}

sf::Sprite Target::getSprite()
{
    return moonSprite;
}

sf::CircleShape Target::getDebugCircle()
{
    return moonColliderVisualized;
}

sf::Texture Target::getTexture()
{
    return moonTexture;
}