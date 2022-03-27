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
#include "RocketPopulation.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
RocketPopulation::RocketPopulation(sf::RenderWindow* hwnd) : window(hwnd)
{
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

//////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
void RocketPopulation::update(float dt, Obstacle* obstacle)
{
    // Update each rockets position according the velocity genes returned from each rockets DNA
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->update(dt, obstacle);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void RocketPopulation::render()
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->render();
    }

    // Render the best rocket on top of all other rockets
    rockets[bestIndex]->render();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

Rocket* RocketPopulation::determineBestRocket()
{
    float lowestMag = rockets[0]->getDistanceToTarget();
    bestIndex = 0;

    for (int i = 0; i < rockets.size(); ++i)
    {
        if (rockets[i]->getDistanceToTarget() < lowestMag)
        {
            lowestMag = rockets[i]->getDistanceToTarget();
            bestIndex = i;
        }
    }

    return rockets[bestIndex];
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//void RocketPopulation::clearMatingPool()
//{
//    matingPool.clear();
//}

//////////////////////////////////////////////////////////////////////////////////////////////////

void RocketPopulation::initPopulation()
{
    for (int i = 0; i < POPULATION_SIZE; ++i)
    {
        rockets.push_back(new Rocket(window));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void RocketPopulation::fitness(Target* target)
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        rockets[i]->assessFitness(target);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool RocketPopulation::selection(Target* target)
{
    // First step of selection is to calculate the fitness of each rocket
    fitness(target);

    // Clear mating pool ready for repopulation
    matingPool.clear();

    // The next step of selection is to build a mating pool
    return populateMatingPool();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////

int RocketPopulation::getMatingPoolSize()
{
    return matingPool.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool RocketPopulation::populateMatingPool()
{
    double totalFitness = 0.0;
    totalFitness = getTotalFitness();
    double fitnessNormed = 0.0;
    int n = 0;
    float fitnessScore = 0.0f;

    // Loop over all the rockets and get their fitness scores
    for (int i = 0; i < rockets.size(); ++i)
    {
        fitnessScore = rockets[i]->getFitnessScore();
        // Map to 0 - 1
        fitnessNormed = mapRange(0, totalFitness, 0, 1, fitnessScore);
        //fitnessNormed = fitnessScore / totalFitness;
        n = std::floor(fitnessNormed * POPULATION_SIZE);
        // n*2 was just to beef up the numbers in the mating pool as sometimes the mating pool would end up at zero
        // Still not sure why this was happening and needs further investigation, seems to be ok for now,
        // it may have been getting caused by some other bug which has since been pulverized to smithereens
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
        std::cout << "Mating Pool is Empty, ";

        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void RocketPopulation::reproduction()
{
    for (int i = 0; i < rockets.size(); ++i)
    {
        // Get 2 random parents from the mating pool
        int randIndexA = (int)rand() % matingPool.size();
        int randIndexB = (int)rand() % matingPool.size();
        
        // Get their DNA sequences
        parentA_DNA = matingPool[randIndexA].getDNASequence();
        parentB_DNA = matingPool[randIndexB].getDNASequence();

        // Create a new DNA strand for the child
        childDNA = parentA_DNA.crossover(parentB_DNA);

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

//////////////////////////////////////////////////////////////////////////////////////////////////

int RocketPopulation::getGeneration()
{
    return generation;
}

//////////////////////////////////////////////////////////////////////////////////////////////////