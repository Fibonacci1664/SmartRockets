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
        population->render();
        ++lifeCounter; 
    }
    else
    {
        lifeCounter = 0;

        population->selection();
        float distance = population->determineBestRocket();

        // Test if found target, if distance is < 20 px
        if (distance <= 20)
        {
            // Target found
            return true;
        }

        population->reproduction();
    }

    return false;
}
