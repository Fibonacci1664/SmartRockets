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
	bool selection();
	bool reproduction();
	void updateBestRocketAndUI();
	void refresh();
	int getGenerationToSolve();

private:
	void initTarget();
	void initObstacle();
	void initWorld();
	void loadTexture();
	void beginDraw();
	void endDraw();

	sf::RenderWindow* window;
	Target* target;
	GeneticAlgorithm* GA;
	Obstacle* obstacle;
	UI* ui;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	int generation;
};