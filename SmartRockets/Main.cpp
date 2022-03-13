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

//void SFMLtest()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//}