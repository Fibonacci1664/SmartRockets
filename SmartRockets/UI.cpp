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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "UI.h"
#include <iostream>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
UI::UI(sf::RenderWindow* hwnd) : window(hwnd)
{
	generation = 0;
	lifeCyclesRemaining = 0;
	closestMagnitude = 0;

	initUI();
}

UI::~UI()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	closestMagnitudeText.setString("Closest Rockets Magnitude to Target #: " + std::to_string(closestMagnitude));
	closestMagnitudeText.setCharacterSize(14);
	closestMagnitudeText.setFillColor(sf::Color::Red);
	closestMagnitudeText.setOutlineColor(sf::Color::Black);
	closestMagnitudeText.setOutlineThickness(1.0f);
	closestMagnitudeText.setPosition(20.0f, 115.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::loadFont()
{
	if (!font.loadFromFile("res/fonts/kenvector_future_thin.ttf"))
	{
		std::cout << "Error loading font\n";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::update(float dt, int gen, int lifeCycles)
{
	generation = gen;
	lifeCyclesRemaining = lifeCycles;

	generationText.setString("Generation #: " + std::to_string(generation));
	lifeCyclesText.setString("Life Cycles Remaining #: " + std::to_string(359 - lifeCyclesRemaining));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::updateMagnitudeUI()
{
	closestMagnitudeText.setString("Closest Rockets Magnitude to Target #: " + std::to_string(closestMagnitude) + " Pixels");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::render()
{
	window->draw(generationText);
	window->draw(lifeCyclesText);
	window->draw(closestMagnitudeText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::setClosestRocketMagnitude(int mag)
{
	closestMagnitude = mag;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////