/*
 * This is the UI class and handles
 *		- Initialisation of UI elements.
 *		- Rendering of the UI.
 *		- Updating the UI with the data.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "UI.h"
#include <iostream>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
UI::UI(sf::RenderWindow* hwnd) : window(hwnd)
{
	generation = 0;
	lifeCyclesRemaining = 0;
	closestMagnitude = 0;
	matingPoolSize = 0;
	totalTime = 0;
	hours = 0;
	mins = 0;
	secs = 0;

	initUI();
}

UI::~UI()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
void UI::initUI()
{
	loadFont();

	// Set up the Generation text
	generationText.setFont(font);
	generationText.setString("Generation #: " + std::to_string(generation));
	generationText.setCharacterSize(14);
	generationText.setFillColor(sf::Color::Red);
	generationText.setOutlineColor(sf::Color::Black);
	generationText.setOutlineThickness(1.0f);
	generationText.setPosition(20.0f, 15.0f);

	// Set up the Life Cycles Remaining text
	lifeCyclesText.setFont(font);
	lifeCyclesText.setString("Life Cycles Remaining #: " + std::to_string(lifeCyclesRemaining));
	lifeCyclesText.setCharacterSize(14);
	lifeCyclesText.setFillColor(sf::Color::Red);
	lifeCyclesText.setOutlineColor(sf::Color::Black);
	lifeCyclesText.setOutlineThickness(1.0f);
	lifeCyclesText.setPosition(20.0f, 65.0f);
	
	// Set up the Closest Magnitude text
	closestMagnitudeText.setFont(font);
	closestMagnitudeText.setString("Best Magnitude Without Hitting Obstacle #: " + std::to_string(closestMagnitude));
	closestMagnitudeText.setCharacterSize(14);
	closestMagnitudeText.setFillColor(sf::Color::Red);
	closestMagnitudeText.setOutlineColor(sf::Color::Black);
	closestMagnitudeText.setOutlineThickness(1.0f);
	closestMagnitudeText.setPosition(20.0f, 115.0f);
	
	// Set up the total time taken text
	totalTimeTakenText.setFont(font);
	totalTimeTakenText.setString("Total Time Taken: " + std::to_string(hours) + "hrs " + std::to_string(mins) + "mins " + std::to_string(secs) + "secs");
	totalTimeTakenText.setCharacterSize(14);
	totalTimeTakenText.setFillColor(sf::Color::Red);
	totalTimeTakenText.setOutlineColor(sf::Color::Black);
	totalTimeTakenText.setOutlineThickness(1.0f);
	totalTimeTakenText.setPosition(20.0f, 165.0f);
	
	// Set up the mating pool size text
	matingPoolSizeText.setFont(font);
	matingPoolSizeText.setString("Mating Pool Size #: " + std::to_string(matingPoolSize));
	matingPoolSizeText.setCharacterSize(14);
	matingPoolSizeText.setFillColor(sf::Color::Red);
	matingPoolSizeText.setOutlineColor(sf::Color::Black);
	matingPoolSizeText.setOutlineThickness(1.0f);
	matingPoolSizeText.setPosition(20.0f, 215.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void UI::loadFont()
{
	if (!font.loadFromFile("res/fonts/kenvector_future_thin.ttf"))
	{
		std::cout << "Error loading font\n";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void UI::update(float dt, int gen, int lifeCycles, int matingPoolSz)
{
	generation = gen;
	lifeCyclesRemaining = lifeCycles;
	matingPoolSize = matingPoolSz;
	totalTime += dt;
	secs = totalTime;
	
	if (totalTime >= 60)
	{
		++mins;

		if (mins >= 60)
		{
			++hours;
			mins = 0;
		}

		totalTime = 0;
	}

	generationText.setString("Generation #: " + std::to_string(generation));
	lifeCyclesText.setString("Life Cycles Remaining #: " + std::to_string(659 - lifeCyclesRemaining));
	totalTimeTakenText.setString("Total Time Taken: " + std::to_string(hours) + "hrs " + std::to_string(mins) + "mins " + std::to_string(secs) + "secs");
	matingPoolSizeText.setString("Mating Pool Size #: " + std::to_string(matingPoolSize));
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void UI::updateMagnitudeUI()
{
	closestMagnitudeText.setString("Best Magnitude Without Hitting Obstacle #: " + std::to_string(closestMagnitude));
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void UI::render()
{
	window->draw(generationText);
	window->draw(lifeCyclesText);
	window->draw(closestMagnitudeText);
	window->draw(totalTimeTakenText);
	window->draw(matingPoolSizeText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void UI::setClosestRocketMagnitude(int mag)
{
	closestMagnitude = mag;
}

//////////////////////////////////////////////////////////////////////////////////////////////////