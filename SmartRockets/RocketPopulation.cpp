#include "RocketPopulation.h"

RocketPopulation::RocketPopulation(sf::RenderWindow* hwnd) : window(hwnd)
{
    target = sf::CircleShape(20);
    target.setFillColor(sf::Color::Red);
    target.setPosition(640, 20);
    initPopulation();
}

RocketPopulation::~RocketPopulation()
{

}

void RocketPopulation::update(float dt)
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->update(dt);
    }
}

void RocketPopulation::render()
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->render();
    }
}

void RocketPopulation::initPopulation()
{
    for (int i = 0; i < POPULATION_SIZE; ++i)
    {
        rockets[i] = new Rocket(window, target);
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

    // The next step of selection is to build a mating pool
    populateMatingPool();
}

void RocketPopulation::populateMatingPool()
{
    // Loop over all the rockets and get their fitness scores
    for (int i = 0; i < rockets.size(); ++i)
    {
        float n = rockets[i]->getFitnessScore();

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
        Rocket* child = new Rocket(window, target);

        // Set that child Rockets DNA sequence
        child->setDNASequence(childDNA);

        // Overwrite the current Rocket at index position with that child Rocket object
        rockets[i] = child;
    }
}