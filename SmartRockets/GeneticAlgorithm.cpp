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
#include "GeneticAlgorithm.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
GeneticAlgorithm::GeneticAlgorithm(sf::RenderWindow* hwnd) : window(hwnd)
{
    population = new RocketPopulation(window);
    closestRocket = nullptr;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    if (population)
    {
        delete population;
        population = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
void GeneticAlgorithm::update(float dt, Obstacle* obstacle)
{
    // Update the rocket population
    population->update(dt, obstacle);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::render()
{
    population->render();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool GeneticAlgorithm::selection(Target* target)
{
    // Get fitness scores for each rocket (magnitude to target)
    return population->selection(target);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::updateClosestRocket()
{
    // Determine closest rocket
    closestRocket = population->determineBestRocket();

    // Change the colour of the collider of that rocket
    closestRocket->setRocketColliderColour();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool GeneticAlgorithm::checkIfFoundTarget(Target* target)
{
    // Carry out intersection checks between the closest rocket and the target moon
    bool targetFound = closestRocket->checkItersection(target);

    if (targetFound)
    {
        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void GeneticAlgorithm::reproduction()
{
    population->reproduction();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int GeneticAlgorithm::getGeneration()
{
    return population->getGeneration();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int GeneticAlgorithm::getMatingPoolSize()
{
    return population->getMatingPoolSize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

Rocket* GeneticAlgorithm::getClosestRocket()
{
    return closestRocket;
}

//////////////////////////////////////////////////////////////////////////////////////////////////