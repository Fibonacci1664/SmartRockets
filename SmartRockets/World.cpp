#include "World.h"

World::World(sf::RenderWindow* hwnd) : window(hwnd)
{
	initWorld();
}

World::~World()
{

}

void World::update(float dt)
{
	GA->update(dt);
}

void World::render()
{
	GA->render();
}

bool World::selectionAndReproduction()
{
	return GA->selectionAndReproduction();
}

void World::initWorld()
{
	GA = new GeneticAlgorithm(window);
}