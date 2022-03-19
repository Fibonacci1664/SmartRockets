#include "World.h"
#include <iostream>

World::World(sf::RenderWindow* hwnd) : window(hwnd)
{
	initWorld();
}

World::~World()
{

}

void World::update(float dt, int cycles)
{
	// Get the latest generation
	generation = GA->getGeneration();

	GA->update(dt);
	ui->update(dt, generation, cycles);
}

void World::beginDraw()
{
	window->clear(sf::Color::Black);
}

void World::render()
{
	beginDraw();

	window->draw(bgSprite);
	ui->render();
	GA->render();

	endDraw();
}

void World::refresh()
{
	beginDraw();

	window->draw(bgSprite);
	ui->render();
	GA->render();

	endDraw();
}

void World::endDraw()
{
	window->display();
}

bool World::selectionAndReproduction()
{
	// Carry out selection, i.e. generate fitness scores
	GA->selection();

	// Update the colour of the closest rocket and the UI's magnitude
	GA->updateClosestRocket();
	ui->setClosestRocketMagnitude(GA->getClosestRocket()->getMagnitude());
	ui->updateMagnitudeUI();

	// Redraw everything to reflect the colour change of the closest rocket and UI update
	refresh();

	// Check if the was an intersection of the closest rocket and the target
	if (GA->checkIfFoundTarget())
	{
		return true;
	}

	// If not then carry out reproduction for the next generation
	GA->reproduction();

	return false;
}

void World::initWorld()
{
	loadTexture();

	bgTexture.setSmooth(true);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(5.0f, 2.8125f);

	GA = new GeneticAlgorithm(window);
	ui = new UI(window);
	generation = GA->getGeneration();
}

void World::loadTexture()
{
	if (!bgTexture.loadFromFile("res/sprites/blue.png"))
	{
		std::cout << "Error loading background texture\n";
	}
}