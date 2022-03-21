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
#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UI
{
public:
	UI(sf::RenderWindow* window);
	~UI();

	void update(float dt, int gen, int lifeCycles, int matingPoolSz);
	void updateMagnitudeUI();
	void render();
	void setClosestRocketMagnitude(int mag);

private:
	void initUI();
	void loadFont();

	sf::RenderWindow* window;
	sf::Font font;
	sf::Text generationText;
	sf::Text lifeCyclesText;
	sf::Text closestMagnitudeText;
	sf::Text totalTimeTakenText;
	sf::Text matingPoolSizeText;

	int generation;
	int lifeCyclesRemaining;
	int closestMagnitude;	// Truncate to int
	int matingPoolSize;
	int hours;
	int mins;
	int secs;
	float totalTime;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////