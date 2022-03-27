/*
 * This is the Rocket Population class and handles: -
 *		- A vector container of Rocket object pointers - the population
 *		- A vector container of Rocket objects - the mating pool
 *		- A single Rocket pointer for the child Rocket object created during reproduction
 *		- 3 DNA objects, 1 for each parent, and 1 for the child
 *
 * The class also handles calling the fitness function, selection, and reproduction
 * It also populates the mating pool and keeps track of the "best" rocket
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <vector>
#include "Rocket.h"
#include "Target.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
extern int POPULATION_SIZE;

//////////////////////////////////////////////////////////////////////////////////////////////////

class RocketPopulation
{
public:
    RocketPopulation(sf::RenderWindow* hwnd);
    ~RocketPopulation();

    void update(float dt, Obstacle* obstacle);
    void render();
    
    Rocket* determineBestRocket();
    //void clearMatingPool();   
    bool selection(Target* target);
    void reproduction();

    int getGeneration();
    int getMatingPoolSize();

private:
    void fitness(Target* target);
    double getTotalFitness();
    double mapRange(double a1, double a2, double b1, double b2, double s);
    void initPopulation();  
    bool populateMatingPool();

    sf::RenderWindow* window;

    Rocket* child;
    DNA parentA_DNA;
    DNA parentB_DNA;
    DNA childDNA;

    std::vector<Rocket*> rockets;
    std::vector<Rocket> matingPool;

    int generation;
    int bestIndex;
};

//////////////////////////////////////////////////////////////////////////////////////////////////