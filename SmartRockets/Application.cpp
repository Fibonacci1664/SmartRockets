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
#include <chrono>
#include <fstream>

int POPULATION_SIZE = 10;
int MUTATION_RATE = 1;
bool TESTING = true;

// Output to CSV file for creating graphs of data
std::ofstream SR_data("SmartRockets_Pop_10.csv");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
Application::Application(int width, int height) : windowWidth(width), windowHeight(height)
{
    lifetime = 660;     // If you change this REMEMBER to update the DNA class for gene size to the same value and the UI for updating the gens remaining, really need to improve this!
    lifeCounter = 0;
    totalTime = 0.0f;

    initWindow();
}

Application::~Application()
{
    if (theWorld)
    {
        delete theWorld;
        theWorld = nullptr;
    }
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

void Application::update()
{
    int testNum = 0;
    int numOfTests = 5;
    bool hasFoundTarget = false;
    theWorld = new World(&window);

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        if (TESTING)
        {
            while (testNum < numOfTests)
            {
                runLoop();

                int genToSolve = theWorld->getGenerationToSolve();

                SR_data << '\n';
                SR_data << (testNum + 1) << "," << POPULATION_SIZE << "," << MUTATION_RATE << "," << genToSolve << "," << totalTime;

                ++testNum;

                // Zero the timer
                totalTime = 0.0f;

                // Clean up old world
                delete theWorld;
                theWorld = nullptr;

                // Create a new world ready for the next loop
                theWorld = new World(&window);
            }
        }
        else
        {
            runLoop();
        }

        break;
    }
}

void Application::runLoop()
{
    bool allRocketsDead = false;
    bool targetNotFound = false;
    bool hasFoundTarget = false;
    
    // Initialise objects for delta time
    sf::Clock clock;
    float deltaTime = 0.0f;

    // If the game isn't over, keep processing stuff
    while (!hasFoundTarget)
    {
        processWindowEvents();

        // Calculate delta time. How much time has passed 
        // since it was last calculated (in seconds) and restart the clock.
        deltaTime = clock.restart().asSeconds();

        // Accumulate the total time for testing and outputting to csv.
        totalTime += deltaTime;

        if (lifeCounter < lifetime)
        {
            theWorld->update(deltaTime, lifeCounter);
            theWorld->render();

            ++lifeCounter;
        }
        else
        {
            lifeCounter = 0;

            allRocketsDead = theWorld->selection();

            if (allRocketsDead)
            {
                targetNotFound = true;
                break;
            }

            theWorld->updateBestRocketAndUI();

            hasFoundTarget = theWorld->reproduction();
        }
    }

    if (targetNotFound)
    {
        std::cout << "Target Not Found!\n";
    }

    std::cout << "Target Found!\n";
}

void Application::setUpCSV()
{
    SR_data << "World #" << "," << "Total Population" << "," << "Mutation Rate %" << "," << "# Gen To Solve" << "," << "Time Taken (s)";
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
            case sf::Event::KeyPressed:
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && displayDebug)
                {
                    displayDebug = false;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !displayDebug)
                {
                    displayDebug = true;
                }

                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////