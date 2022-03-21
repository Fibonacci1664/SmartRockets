#pragma once
#include <SFML/Graphics.hpp>

extern bool displayDebug;

class Obstacle
{
public:
	Obstacle(sf::RenderWindow* hwnd);
	~Obstacle();

	void update(float dt);
	void render();

	sf::FloatRect getCollisonBox();

private:
	//void loadTexture();
	void initObstacle();

	/*sf::Texture obstacleTexture;
	sf::Sprite obstacleSprite;*/

	sf::RenderWindow* window;

	// Debug box for rocketmoonColliderVisualized, this is AABB, needs improved for OBB
	sf::RectangleShape obstacle;
	sf::RectangleShape obstacleDebugBox;
	sf::FloatRect obstacleCollisionBox;

};

