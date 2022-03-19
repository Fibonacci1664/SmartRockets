#pragma once
#include "RocketPopulation.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(sf::RenderWindow* hwnd);
    ~GeneticAlgorithm();

    void update(float dt);
    void render();
    bool selectionAndReproduction();

private:
    sf::RenderWindow* window;
    RocketPopulation* population;
};

