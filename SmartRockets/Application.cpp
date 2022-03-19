/*
 * This is the Application class and handles
 *		- Window creation.
 *		- Polling window events.
 *		- The main GA loop.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // INCLUDES
#include "Application.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
Application::Application(int width, int height) : windowWidth(width), windowHeight(height)
{
    initWindow();
}

Application::~Application()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
void Application::initWindow()
{
    window.create(sf::VideoMode(windowWidth, windowHeight), "SMART ROCKETS!");
    // NEVER have both vSync AND framerate limit, it's either, or, NEVER both!
    // If you find vSync is having no effect, check graphics driver's settings and change vSync from "off" to "controlled by application"
    //window.setVerticalSyncEnabled(true);    // Ensure the application runs at the same frequency as the monitor's refresh rate
    window.setFramerateLimit(60);           // Request a fixed framerate, diffrent OS may output slightly different FPS

    // Get the native screen res
    int nativeScreenWidth = sf::VideoMode::getDesktopMode().width;
    int nativeScreenHeight = sf::VideoMode::getDesktopMode().height;

    // Place the viewing window in the centre of the screen
    window.setPosition(sf::Vector2i((nativeScreenWidth * 0.5f) - (windowWidth * 0.5f), (nativeScreenHeight * 0.5f) - (windowHeight * 0.5f)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Application::run()
{
    bool hasFoundTarget = false;

    GA = new GeneticAlgorithm(&window);

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Initialise objects for delta time
        sf::Clock clock;
        float deltaTime;

        // If the game isn't over, keep processing stuff
        while (!hasFoundTarget)
        {
            processWindowEvents();

            // Calculate delta time. How much time has passed 
            // since it was last calculated (in seconds) and restart the clock.
            deltaTime = clock.restart().asSeconds();

            // run genetic algo here!
            hasFoundTarget = GA->run(deltaTime);
        }

        std::cout << "Target Found!\n";

        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Application::processWindowEvents()
{
    // Check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    unsigned int n_buts = 0;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::Resized:
            {
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////