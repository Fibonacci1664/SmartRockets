#include "GeneticAlgorithm.h"
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(sf::RenderWindow* hwnd) : window(hwnd)
{
    population = new RocketPopulation(window);
    closestRocket = nullptr;
}

GeneticAlgorithm::~GeneticAlgorithm()
{

}

void GeneticAlgorithm::update(float dt)
{
    // Update the rocket population
    population->update(dt);
}

void GeneticAlgorithm::render()
{
    population->render();
}

void GeneticAlgorithm::selection()
{
    // Get fitness scores for each rocket (magnitude to target)
    population->selection();
}

void GeneticAlgorithm::updateClosestRocket()
{
    // Determine closest rocket
    closestRocket = population->determineBestRocket();

    // Change the colour of the collider of that rocket
    closestRocket->setRocketColliderColour();
}

bool GeneticAlgorithm::checkIfFoundTarget()
{
    // Carry out intersection checks between the closest rocket and the target moon
    bool targetFound = closestRocket->checkItersection();

    if (targetFound)
    {
        return true;
    }

    return false;
}

void GeneticAlgorithm::reproduction()
{
    population->reproduction();
}

//bool GeneticAlgorithm::selectionAndReproduction()
//{
//    
//
//    
//
//    
//
//    
//
//    // Clean up the closest rocket from the previous generation
//    /*delete closestRocket;
//    closestRocket = nullptr;*/
//
//    return false;
//}

int GeneticAlgorithm::getGeneration()
{
    return population->getGeneration();
}

Rocket* GeneticAlgorithm::getClosestRocket()
{
    return closestRocket;
}
