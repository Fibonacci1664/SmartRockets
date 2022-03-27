/*
 * This is the GA class and handles: -
 *		- Creating a rocket population object
 *		- Keeping a copy of the closest rocket
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include "RocketPopulation.h"
#include "Target.h"
#include "Obstacle.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(sf::RenderWindow* hwnd);
    ~GeneticAlgorithm();

    void update(float dt, Obstacle* obstacle);
    void render();
    
    bool selection(Target* target);
    void updateClosestRocket();
    bool checkIfFoundTarget(Target* target);
    void reproduction();
    int getGeneration();
    int getMatingPoolSize();

    Rocket* getClosestRocket();

private:
    sf::RenderWindow* window;

    RocketPopulation* population;
    Rocket* closestRocket;
};

//////////////////////////////////////////////////////////////////////////////////////////////////