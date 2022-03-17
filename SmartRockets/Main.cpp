#include<SFML/Graphics.hpp>
#include "Application.h"

// GLOBALS
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
	app.run();

	/*sf::CircleShape target(20);
	target.setFillColor(sf::Color::Red);*/
	
	return 0;
}