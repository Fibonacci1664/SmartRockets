#include "Obstacle.h"

Obstacle::Obstacle(sf::RenderWindow* hwnd) : window(hwnd)
{
	initObstacle();
}

Obstacle::~Obstacle()
{

}

void Obstacle::update(float dt)
{

}

void Obstacle::render()
{
	window->draw(obstacle);
	
	if(displayDebug)
	{
		window->draw(obstacleDebugBox);
	}
}

void Obstacle::initObstacle()
{
	// Create a rect obstacle
	obstacle = sf::RectangleShape(sf::Vector2f(250.0f, 10.0f));
	obstacle.setFillColor(sf::Color::Red);
	//obstacle.setOrigin(200.0, 5.0f);
	obstacle.setPosition(640.0f - obstacle.getSize().x * 0.5f, 480.0f - obstacle.getSize().y * 0.5f);

	// Create a float rect to represent the collision box around the above rect obstacle
	obstacleCollisionBox = sf::FloatRect(obstacle.getPosition().x, obstacle.getPosition().y, obstacle.getSize().x, obstacle.getSize().y);

	if (displayDebug)
	{
		// Create another rect to visualise the float rect collider
		obstacleDebugBox = sf::RectangleShape(sf::Vector2f(400.0f, 10.0f));
		obstacleDebugBox.setFillColor(sf::Color(0, 0, 0, 0));
		obstacleDebugBox.setOutlineColor(sf::Color::Yellow);
		obstacleDebugBox.setOutlineThickness(1.0f);
		obstacleDebugBox.setRotation(obstacle.getRotation());
		obstacleDebugBox.setPosition(sf::Vector2f(obstacleCollisionBox.left, obstacleCollisionBox.top));
		obstacleDebugBox.setSize(sf::Vector2f(obstacleCollisionBox.width, obstacleCollisionBox.height));
	}
}

sf::FloatRect Obstacle::getCollisonBox()
{
	return obstacleCollisionBox;
}
