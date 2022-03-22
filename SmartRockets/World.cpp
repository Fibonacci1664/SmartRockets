#include "World.h"
#include <iostream>

World::World(sf::RenderWindow* hwnd) : window(hwnd)
{
	initWorld();
	initTarget();
	initObstacle();
}

World::~World()
{
	if (GA)
	{
		delete GA;
		GA = nullptr;
	}

	if (ui)
	{
		delete ui;
		ui = nullptr;
	}
}

void World::update(float dt, int cycles)
{
	// Get the latest generation
	generation = GA->getGeneration();
	GA->update(dt, obstacle);

	int matingPoolSize = GA->getMatingPoolSize();

	ui->update(dt, generation, cycles, matingPoolSize);
}

void World::beginDraw()
{
	window->clear(sf::Color::Black);
}

void World::render()
{
	beginDraw();

	window->draw(bgSprite);

	if (target)
	{
		target->render();
	}

	if (obstacle)
	{
		obstacle->render();
	}

	GA->render();
	ui->render();

	endDraw();
}

void World::refresh()
{
	beginDraw();

	window->draw(bgSprite);

	if (target)
	{
		target->render();
	}

	if (obstacle)
	{
		obstacle->render();
	}

	GA->render();
	ui->render();

	endDraw();
}

int World::getGenerationToSolve()
{
	return generation;
}

void World::endDraw()
{
	window->display();
}

bool World::selection()
{
	// Carry out selection, i.e. generate fitness scores
	return GA->selection(target);
}

void World::updateBestRocketAndUI()
{
	// Update the colour of the closest rocket and the UI's magnitude
	GA->updateClosestRocket();
	ui->setClosestRocketMagnitude(GA->getClosestRocket()->getDistanceToTarget());
	ui->updateMagnitudeUI();

	// Redraw everything to reflect the colour change of the closest rocket and UI update
	refresh();
}

bool World::reproduction()
{
	// Check if there was an intersection of the closest rocket and the target
	if (GA->checkIfFoundTarget(target))
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

void World::initTarget()
{
	target = new Target(window);
}

void World::initObstacle()
{
	obstacle = new Obstacle(window);
}

void World::loadTexture()
{
	if (!bgTexture.loadFromFile("res/sprites/blue.png"))
	{
		std::cout << "Error loading background texture\n";
	}
}