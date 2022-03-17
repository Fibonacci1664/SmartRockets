#include "Rocket.h"
#include <cmath>
#include <iostream>

constexpr auto PI = 3.14159265359;

Rocket::Rocket(sf::RenderWindow* hwnd) : window(hwnd)
{
    rocketPosition = sf::Vector2f(640.0f, 670.0f);
    moonPosition = sf::Vector2f(640.0f, 50.0f);
    velocity = sf::Vector2f(0.0f, 0.0f);
    accel = sf::Vector2f(0.0f, 0.0f);

    loadTextures();
    initRocket();
    initTarget();
}

Rocket::~Rocket()
{

}

void Rocket::update(float dt)
{
    sf::Vector2f accelGeneVector = dna.getGene(geneCounter);
    addForce(accelGeneVector, dt);
    ++geneCounter;

    // Reset the gene indexing
    if (geneCounter == 10)
    {
        geneCounter = 0;
    }
}

void Rocket::render()
{
    window->draw(rocketSprite);
    window->draw(moonSprite);
}

void Rocket::assessFitness()
{
    sf::Vector2f dirToTarget = moonSprite.getPosition() - rocketPosition;
    magnitude = calculateMagnitude(dirToTarget);
    fitnessScore = std::powf(1 / magnitude, 2);
}

float Rocket::getMagnitude()
{
    return magnitude;
}

float Rocket::getFitnessScore()
{
    return fitnessScore;
}

DNA Rocket::getDNASequence()
{
    return dna;
}

void Rocket::setDNASequence(DNA newDNA)
{
    dna = newDNA;
}

sf::Vector2f Rocket::lerp(sf::Vector2f v1, sf::Vector2f v2, float dt)
{
    return v1 * dt + (1 - dt) * v2;
}

sf::Vector2f Rocket::calculateUnitVector(sf::Vector2f vec)
{
    float l_magnitude = calculateMagnitude(vec);

    float unitVecX = 0.0f;
    float unitVecY = 0.0f;

    // Check for divide by zero
    if (l_magnitude != 0)
    {
        unitVecX = vec.x / l_magnitude;
        unitVecY = vec.y / l_magnitude;
    }

    sf::Vector2f unitVec = sf::Vector2f(unitVecX, unitVecY);

    return unitVec;
}

float Rocket::calculateMagnitude(sf::Vector2f vec)
{
    float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    return mag;
}

sf::Vector2f Rocket::limiter(float topSpeed)
{
    // Get the direction of the velocity vector
    float thetaRad = std::atan2f(velocity.y, velocity.x);
    int thetaDeg = (thetaRad * 180) / 3.14159265359f;

    // Test magnitude of current velocity vector
    float mag = calculateMagnitude(velocity);

    sf::Vector2f newVel;

    if (mag > topSpeed)
    {
        mag = topSpeed;

        // v = ||v|| * cos(theta)i + ||v|| * sin(theta)j
        newVel = sf::Vector2f(mag * std::cos(thetaDeg), mag * std::sin(thetaDeg));
    }
    else
    {
        newVel = velocity;
    }

    return newVel;
}

void Rocket::addForce(sf::Vector2f newForce, float dt)
{
    // Normalise
    sf::Vector2f accel = calculateUnitVector(newForce);
    // Scale
    //accel *= speed;
    // Add the accel to the velocity
    velocity += accel;
    // Ensure that the velocity is limited to max magnitude of 10
    velocity = limiter(maxSpeed);
    // Update rockets position using velocity
    rocketPosition += velocity;
    // Set new rocket position
    rocketSprite.setPosition(rocketPosition);
}

void Rocket::initTarget()
{
    moonTexture.setSmooth(true);
    moonSprite.setTexture(moonTexture);
    moonSize = moonTexture.getSize();
    moonSprite.setOrigin(moonSize.x * 0.5f, moonSize.y);
    moonSprite.setPosition(moonPosition);
    moonSprite.setRotation(-90.0f);
    moonSprite.setScale(0.2f, 0.2f);
}

void Rocket::initRocket()
{
    rocketTexture.setSmooth(true);
    rocketSprite.setTexture(rocketTexture);
    rocketSize = rocketTexture.getSize();
    rocketSprite.setOrigin(rocketSize.x * 0.5f, 0.0f);
    rocketSprite.setPosition(rocketPosition);
    rocketSprite.setRotation(-90.0f);
    rocketSprite.setScale(0.05f, 0.05f);
}

void Rocket::loadTextures()
{
    if (!rocketTexture.loadFromFile("res/RocketSprite.png"))
    {
        std::cout << "Error loading rocket texture\n";
    }

    if (!moonTexture.loadFromFile("res/AsteroidSprite.png"))
    {
        std::cout << "Error loading moon texture\n";
    }
}