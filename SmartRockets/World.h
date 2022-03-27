/*
 * This is the World class and handles all things contained within the World, namely: -
 *		- Creating a Target object
 *		- Creating a GA algorithm object
 *		- Creating an obstacle object
 *		- Creating a UI object
 *
 * This class also handle calling the GA functions such as update, render, selection, and reproduction
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GeneticAlgorithm.h"
#include "Target.h"
#include "UI.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

class World
{
public:
	World(sf::RenderWindow* hwnd);
	~World();

	void update(float dt, int cycles);
	void render();
	bool selection();
	bool reproduction();
	void updateBestRocketAndUI();
	void refresh();
	int getGenerationToSolve();

private:
	void initTarget();
	void initObstacle();
	void initWorld();
	void loadTexture();
	void beginDraw();
	void endDraw();

	sf::RenderWindow* window;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	Target* target;
	GeneticAlgorithm* GA;
	Obstacle* obstacle;
	UI* ui;

	int generation;
};

//////////////////////////////////////////////////////////////////////////////////////////////////