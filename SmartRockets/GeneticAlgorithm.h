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
    int lifetime = 360;      // 1 Generation every ~6 sec, assuming 60 FPS
    int lifeCounter = 0;
};

