/*
 * This is the Target class and handles: -
 *		- Loading textures and rendering the moon sprite
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

class Target
{
public:
	Target(sf::RenderWindow* hwnd);
	~Target();

	void update(float dt);
	void render();

	sf::Sprite getSprite();
	sf::CircleShape getDebugCircle();
	sf::Texture getTexture();

private:
	void initTarget();
	void initMoonDebug();
	void loadTexture();

	sf::RenderWindow* window;
	sf::Texture moonTexture;
	sf::Sprite moonSprite;

	// Debug circle for moon
	sf::CircleShape moonColliderVisualized;
	sf::Vector2f moonPosition;
	sf::Vector2u moonSize;
};

//////////////////////////////////////////////////////////////////////////////////////////////////