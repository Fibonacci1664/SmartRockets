#include "DNA.h"
#include <cmath>
#include <random>

DNA::DNA()
{
    maxForce = 0.1f;
    createDNAstrand();
}

DNA::~DNA()
{

}

void DNA::createDNAstrand()
{
    for (int i = 0; i < genes.size(); ++i)
    {
        sf::Vector2f randVec = getRandom2DVector();

        // Set this random vec to be the gene of this particular DNA
        genes[i] = randVec;
    }
}

sf::Vector2f DNA::getRandom2DVector()
{
    // Get some random angle 0 - 359
    // We use polar so as not to have any bias towards diagonals if we just used cartesian
    float randTheta = rand() % 360;

    // Radius will always be 1
    float r = 1.0f;

    // Convert random polar coords to cartesian
    float x = r * std::cos(randTheta);
    float y = r * std::sin(randTheta);

    // Create a new 2D vector using the random coords
    sf::Vector2f randVec = sf::Vector2f(x, y);

    // Get some random force 0 - maxForce
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(0.0f, maxForce);
    float randForce = distr(eng);

    // Multiply the random vec in both x & y by the randForce
    randVec.x *= randForce;
    randVec.y *= randForce;

    return randVec;
}

void DNA::mutate()
{
    for (int i = 0; i < genes.size(); ++i)
    {
        int randChance = rand() % 100;

        if (randChance < MUTATION_RATE)
        {
            // Get a new random 2D vector
            sf::Vector2f randVec = getRandom2DVector();

            genes[i] = randVec;
        }
    }
}

DNA DNA::crossover(DNA partner)
{
    DNA child;

    // Pick some random point in the gene strand
    int randPoint = rand() % genes.size();

    for (int i = 0; i < genes.size(); ++i)
    {
        // All indices before the randomly chosen point are
        // populated with one of the parents genes
        if (i < randPoint)
        {
            child.genes[i] = genes[i];
        }
        else
        {
            // All other indices are populated with the other parents genes
            child.genes[i] = partner.genes[i];
        }
    }

    return child;
}

sf::Vector2f DNA::getGene(int indexPos)
{
    return genes[indexPos];
}

const int DNA::getDNALength()
{
    return DNA_LENGTH;
}
