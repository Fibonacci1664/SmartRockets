/*
 * This is the Obstacle class and handles: -
 *		- Setting up a simple SFML rectangle shape with collision box around it
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
extern bool displayDebug;

//////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////