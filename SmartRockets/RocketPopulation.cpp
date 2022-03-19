#include "RocketPopulation.h"
#include <iostream>

RocketPopulation::RocketPopulation(sf::RenderWindow* hwnd) : window(hwnd)
{
    closestRocket = nullptr;
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

    // Trying to draw the closest rocket on top of all other graphics, this is a broken stretch goal
    /*if (closestRocket)
    {
        window->draw(closestRocket->getRocketSprite());

        delete closestRocket;
        closestRocket = nullptr;
    }*/

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


Rocket* RocketPopulation::determineBestRocket()
{
    float lowestMag = rockets[0]->getMagnitude();
    closestRocket = rockets[0];

    for (int i = 0; i < rockets.size(); ++i)
    {
        if (rockets[i]->getMagnitude() < lowestMag)
        {
            lowestMag = rockets[i]->getMagnitude();
            closestRocket = rockets[i];
        }
    }

    return closestRocket;
}

void RocketPopulation::clearMatingPool()
{
    matingPool.clear();
}

void RocketPopulation::initPopulation()
{
    for (int i = 0; i < POPULATION_SIZE; ++i)
    {
        rockets.push_back(new Rocket(window));
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

//                                           a1                     a2                     b1                   b2                   s
double RocketPopulation::mapRange(double minFitnessVal, double totalFitnessVal, double newRangeMin, double newRangeMax, double currFitnessVal)
{
    /*
     *  Given 2 ranges: -
     *      *   [a1, a2]
     *      *   [b1, b2]
     * 
     *      and some value 's' in the range [a1, a2]
     *      is linearly mapped to a value 't' in the range [b1, b2]
     * 
     *               (s - a1) * (b2 - b1)
     *      t = b1 + --------------------
     *                     (a2 - a1)
     * 
     *      t = b1 + (s - a1) * (b2 - b1) / (a2 - a1);
     * 
    */

    float t = newRangeMin + (currFitnessVal - minFitnessVal) * (newRangeMax - newRangeMin) / (totalFitnessVal - minFitnessVal);

    return t;
}

double RocketPopulation::getTotalFitness()
{
    double totalFitnessScore = 0.0f;

    // Calculate the total fitness of the whole population
    for (int i = 0; i < rockets.size(); ++i)
    {
        totalFitnessScore += rockets[i]->getFitnessScore();
    }

    return totalFitnessScore;
}

void RocketPopulation::populateMatingPool()
{
    double totalFitness = getTotalFitness();

    // Loop over all the rockets and get their fitness scores
    for (int i = 0; i < rockets.size(); ++i)
    {
        double fitnessNormed = mapRange(0, totalFitness, 0, 1, rockets[i]->getFitnessScore());
        int n = std::floor(fitnessNormed * 100);

        // Add each member of the population n number of times, this ensures
        // The fittest members have the highest probablity of passing on their genes
        // But also does NOT rule out even the weakest members of the population
        for (int j = 0; j < n; ++j)
        {
            matingPool.push_back(*rockets[i]);
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

        Rocket parentA = matingPool[randIndexA];
        Rocket parentB = matingPool[randIndexB];

        // Get their DNA sequences
        DNA parentA_DNA = parentA.getDNASequence();
        DNA parentB_DNA = parentB.getDNASequence();

        // Create a new DNA strand for the child
        DNA childDNA = parentA_DNA.crossover(parentB_DNA);

        // Chance of mutations
        childDNA.mutate();

        // Create a child rocket
        Rocket* child = new Rocket(window);

        // Set that child Rockets DNA sequence
        child->setDNASequence(childDNA);

        // Clean up all the old rockets
        delete rockets[i];
        rockets[i] = nullptr;

        // Overwrite the current Rocket at index position with that child Rocket object
        rockets[i] = child;
    }
}