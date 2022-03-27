/*
 * This is the Application class and handles
 *		- Window creation.
 *		- Polling window events.
 *		- The main game loop.
 *		- Creation, updating and deletion of all Screen objects.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2021.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include "GeneticAlgorithm.h"
#include "World.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
extern bool displayDebug;

//////////////////////////////////////////////////////////////////////////////////////////////////

class Application
{
public:
	Application(int width, int height);
	~Application();

	void update();
	void runLoop();
	void setUpCSV();

private:
	void initWindow();
	void processWindowEvents();

	sf::RenderWindow window;

	World* theWorld;

	int windowWidth;
	int windowHeight;
	int lifetime;      // 1 Generation every ~11 sec, assuming 60 FPS
	int lifeCounter;

	float totalTime;
};

//////////////////////////////////////////////////////////////////////////////////////////////////