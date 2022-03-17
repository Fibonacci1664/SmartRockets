#include "RocketPopulation.h"

RocketPopulation::RocketPopulation(sf::RenderWindow* hwnd) : window(hwnd)
{
    initPopulation();
}

RocketPopulation::~RocketPopulation()
{

}

void RocketPopulation::update(float dt)
{
    // Update each rockets position according the velocity genes returned from each rockets DNA
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->update(dt);
    }
}

void RocketPopulation::beginDraw()
{
    window->clear(sf::Color::Black);
}

void RocketPopulation::render()
{
    beginDraw();

    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->render();
    }

    endDraw();
}

void RocketPopulation::endDraw()
{
    window->display();
}


float RocketPopulation::determineBestRocket()
{
    float lowestMag = rockets[0]->getMagnitude();

    for (int i = 0; i < rockets.size(); ++i)
    {
        if (rockets[i]->getMagnitude() < lowestMag)
        {
            lowestMag = rockets[i]->getMagnitude();
        }
    }

    return lowestMag;
}

void RocketPopulation::clearMatingPool()
{
    matingPool.clear();
}

void RocketPopulation::initPopulation()
{
    for (int i = 0; i < POPULATION_SIZE; ++i)
    {
        rockets[i] = new Rocket(window);
    }
}

void RocketPopulation::fitness()
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->assessFitness();
    }
}

void RocketPopulation::selection()
{
    // First step of selection is to calculate the fitness of each rocket
    fitness();

    // Clear mating pool ready for repopulation
    matingPool.clear();

    // The next step of selection is to build a mating pool
    populateMatingPool();
}

void RocketPopulation::populateMatingPool()
{
    // Loop over all the rockets and get their fitness scores
    for (int i = 0; i < rockets.size(); ++i)
    {
        float n = rockets[i]->getFitnessScore();
        n *= 100000;

        // Add each member of the population n number of times, this ensures
        // The fittest members have the highest probablity of passing on their genes
        // But also does NOT rule out even the weakest members of the population
        for (int j = 0; j < n; ++j)
        {
            matingPool.push_back(rockets[i]);
        }
    }
}

void RocketPopulation::reproduction()
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        // Get 2 random parents from the mating pool
        int randIndexA = (int)rand() % matingPool.size();
        int randIndexB = (int)rand() % matingPool.size();

        Rocket* parentA = matingPool[randIndexA];
        Rocket* parentB = matingPool[randIndexB];

        // Get their DNA sequences
        DNA parentA_DNA = parentA->getDNASequence();
        DNA parentB_DNA = parentB->getDNASequence();

        // Create a new DNA strand for the child
        DNA childDNA = parentA_DNA.crossover(parentB_DNA);

        // Chance of mutations
        childDNA.mutate();

        // Create a child rocket
        Rocket* child = new Rocket(window);

        // Set that child Rockets DNA sequence
        child->setDNASequence(childDNA);

        // Overwrite the current Rocket at index position with that child Rocket object
        rockets[i] = child;
    }
}