#pragma once
#include "RocketPopulation.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(sf::RenderWindow* hwnd);
    ~GeneticAlgorithm();

    bool run(float dt);

private:
    sf::RenderWindow* window;
    RocketPopulation* population;
    int lifetime = 100;
    int lifeCounter = 0;

};

