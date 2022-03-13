/*
 * This is the Application class and handles
 *		- Window creation.
 *		- Polling window events.
 *		- The main game loop.
 *		- Creation, updating and deletion of all Screen objects.
 *
 * Original @author D. Green.
 *
 * � D. Green. 2021.
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // INCLUDES
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include "GeneticAlgorithm.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Application
{
public:
	Application(int width, int height);
	~Application();

	void update(float dt);
	void render();
	void run();

private:
	void initWindow();
	void processWindowEvents();

	sf::RenderWindow window;

	int windowWidth;
	int windowHeight;

	GeneticAlgorithm* GA;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////