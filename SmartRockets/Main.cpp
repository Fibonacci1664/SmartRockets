#include<SFML/Graphics.hpp>
#include "Application.h"

// GLOBALS
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
	app.update();

	// A simple hack just so that you can see the rocket
	// which has hit the target before the application closes
	system("pause");
	
	return 0;
}