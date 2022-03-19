#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GeneticAlgorithm.h"
#include "Target.h"

class World
{
public:
	World(sf::RenderWindow* hwnd);
	~World();

	void update(float dt);
	void render();
	bool selectionAndReproduction();

private:
	void initWorld();

	sf::RenderWindow* window;
	GeneticAlgorithm* GA;
};