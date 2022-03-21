#include<SFML/Graphics.hpp>
#include "Application.h"

// GLOBALS
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// It's not the prettiest debug because the app currently uses AABB so the
// debug boxes do not rotate with the sprites, this includes the rectangle
// used to visualise the debug box
bool displayDebug = true;

int main()
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	Application app(WINDOW_WIDTH, WINDOW_HEIGHT);
	app.setUpCSV();
	app.update();

	// A simple hack just so that you can see the rocket
	// which has hit the target before the application closes
	system("pause");
	
	return 0;
}