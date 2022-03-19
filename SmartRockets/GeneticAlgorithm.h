#pragma once
#include "RocketPopulation.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(sf::RenderWindow* hwnd);
    ~GeneticAlgorithm();

    void update(float dt);
    void render();
    
    void selection();
    void updateClosestRocket();
    bool checkIfFoundTarget();
    void reproduction();
    int getGeneration();

    Rocket* getClosestRocket();

private:
    sf::RenderWindow* window;
    RocketPopulation* population;
    Rocket* closestRocket;
};

