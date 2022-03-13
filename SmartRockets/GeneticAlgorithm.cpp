#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(sf::RenderWindow* hwnd) : window(hwnd)
{
    population = new RocketPopulation(window);
}

GeneticAlgorithm::~GeneticAlgorithm()
{

}

bool GeneticAlgorithm::run(float dt)
{
    if (lifeCounter < lifetime)
    {
        population->update(dt);
        ++lifeCounter;
    }
    else
    {
        lifeCounter = 0;

        population->fitness();
        population->selection();
        population->reproduction();
    }

    // Fix this!
    return true;
}
