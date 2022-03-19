#include "GeneticAlgorithm.h"
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(sf::RenderWindow* hwnd) : window(hwnd)
{
    population = new RocketPopulation(window);
}

GeneticAlgorithm::~GeneticAlgorithm()
{

}

void GeneticAlgorithm::update(float dt)
{
    population->update(dt);
}

void GeneticAlgorithm::render()
{
    population->render();
}

bool GeneticAlgorithm::selectionAndReproduction()
{
    population->selection();

    // Determine closest rocket
    Rocket* closestRocket = population->determineBestRocket();

    // Change the colour of the collider of that rocket
    closestRocket->setRocketColliderColour();

    // Redraw everything with the newly update closest rocket colour changed
    population->render();

    // Carry out intersection checks between the closest rocket and the target moon
    bool targetFound = closestRocket->checkItersection();

    if (targetFound)
    {
        return true;
    }

    population->reproduction();

    // Clean up the closest rocket from the previous generation
    /*delete closestRocket;
    closestRocket = nullptr;*/

    return false;
}
