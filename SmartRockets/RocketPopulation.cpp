#include "RocketPopulation.h"
#include <iostream>

RocketPopulation::RocketPopulation(sf::RenderWindow* hwnd) : window(hwnd)
{
    //closestRocket = nullptr;
    child = nullptr;
    generation = 1;     // Gen starts at 1 NOT 0
    bestIndex = 0;
    initPopulation();
}

RocketPopulation::~RocketPopulation()
{
    if (rockets.size() > 0)
    {
        for (int i = 0; i < rockets.size(); ++i)
        {
            if (rockets[i])
            {
                delete rockets[i];
                rockets[i] = nullptr;
            }
        }
    }
}

void RocketPopulation::update(float dt, Obstacle* obstacle)
{
    // Update each rockets position according the velocity genes returned from each rockets DNA
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->update(dt, obstacle);
    }
}

void RocketPopulation::render()
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->render();
    }

    // Render the best rocket on top of all other rockets
    rockets[bestIndex]->render();
}

Rocket* RocketPopulation::determineBestRocket()
{
    float lowestMag = rockets[0]->getMagnitude();
    bestIndex = 0;

    for (int i = 0; i < rockets.size(); ++i)
    {
        if (rockets[i]->getMagnitude() < lowestMag)
        {
            lowestMag = rockets[i]->getMagnitude();
            bestIndex = i;
        }
    }

    return rockets[bestIndex];
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

void RocketPopulation::fitness(Target* target)
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->assessFitness(target);
    }
}

bool RocketPopulation::selection(Target* target)
{
    // First step of selection is to calculate the fitness of each rocket
    fitness(target);

    // Clear mating pool ready for repopulation
    matingPool.clear();

    // The next step of selection is to build a mating pool
    return populateMatingPool();
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

int RocketPopulation::getMatingPoolSize()
{
    return matingPool.size();
}

bool RocketPopulation::populateMatingPool()
{
    double totalFitness = 0.0;
    totalFitness = getTotalFitness();
    //totalFitness *= 1000;
    double fitnessNormed = 0.0;
    int n = 0;
    float fitnessScore = 0.0f;

    // Loop over all the rockets and get their fitness scores
    for (int i = 0; i < rockets.size(); ++i)
    {
        //double fitnessNormed = 0.0;
        fitnessScore = rockets[i]->getFitnessScore();
        //fitnessScore *= 100;
        // Map to 0 - 1
        fitnessNormed = mapRange(0, totalFitness, 0, 1, fitnessScore);
        //fitnessNormed = fitnessScore / totalFitness;
        //int n = 0;
        n = std::floor(fitnessNormed * POPULATION_SIZE);
        //n *= 2;

        // Add each member of the population n number of times, this ensures
        // The fittest members have the highest probablity of passing on their genes
        // But also does NOT rule out even the weakest members of the population
        for (int j = 0; j < n; ++j)
        {
            matingPool.push_back(*rockets[i]);
        }
    }

    // If the mating pool is empty it means all the rockets hit the obstacle and so the target is not found, FAIL!
    if (matingPool.empty())
    {
        std::cout << "Mating Pool is Empty, why??\n";

        return true;
    }

    return false;
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
        child = new Rocket(window);

        // Set that child Rockets DNA sequence
        child->setDNASequence(childDNA);

        // Clean up all the old rockets
        delete rockets[i];
        rockets[i] = nullptr;

        // Overwrite the current Rocket at index position with that child Rocket object
        rockets[i] = child;
    }

    // Once we have finished reproducting, we move to the next generation
    ++generation;
}

int RocketPopulation::getGeneration()
{
    return generation;
}
