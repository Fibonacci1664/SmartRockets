#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GeneticAlgorithm.h"
#include "Target.h"
#include "UI.h"

class World
{
public:
	World(sf::RenderWindow* hwnd);
	~World();

	void update(float dt, int cycles);
	void render();
	bool selectionAndReproduction();
	void refresh();

private:
	void initWorld();
	void loadTexture();
	void beginDraw();
	void endDraw();

	sf::RenderWindow* window;
	GeneticAlgorithm* GA;
	UI* ui;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	int generation;
};