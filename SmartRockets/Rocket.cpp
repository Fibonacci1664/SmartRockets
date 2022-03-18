#include "Rocket.h"
#include <cmath>
#include <iostream>

constexpr auto PI = 3.14159265359;

Rocket::Rocket(sf::RenderWindow* hwnd) : window(hwnd)
{
    distanceToTarget = 0.0f;
    fitnessScore = 0.0f;
    magnitude = 0.0f;
    geneCounter = 0;
    maxSpeed = 10.0f;
    speed = 2.0f;

    rocketPosition = sf::Vector2f(640.0f, 670.0f);
    moonPosition = sf::Vector2f(640.0f, 100.0f);
    velocity = sf::Vector2f(0.0f, 0.0f);
    accel = sf::Vector2f(0.0f, 0.0f);

    loadTextures();
    initRocket();
    initTarget();
    initDebug();   
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

    // Update the rockets invisible collision box
    rocketCollisionBox = sf::FloatRect(rocketSprite.getPosition().x, rocketSprite.getPosition().y, rocketSize.x * 0.05f, rocketSize.y * 0.05f);

    // Update the rectangle visualisation of the rockets collision box
    rocketColBoxVisualized.setPosition(sf::Vector2f(rocketCollisionBox.left, rocketCollisionBox.top));
}

void Rocket::render()
{
    window->draw(rocketColBoxVisualized);
    window->draw(moonColliderVisualized);
    window->draw(moonSprite);
    window->draw(rocketSprite);
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
    velocity += accel * dt;
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
    moonSprite.setOrigin(moonSize.x * 0.5f, moonSize.y * 0.5f);
    moonSprite.setPosition(moonPosition);
    moonSprite.setScale(0.2f, 0.2f);
}

void Rocket::initDebug()
{
    initRocketDebug();
    initMoonDebug(); 
}

void Rocket::initRocketDebug()
{
    rocketColBoxVisualized.setFillColor(sf::Color(0, 0, 0, 0));
    rocketColBoxVisualized.setOutlineColor(sf::Color::Magenta);
    rocketColBoxVisualized.setOutlineThickness(1.0f);
    rocketColBoxVisualized.setRotation(rocketSprite.getRotation());
    rocketColBoxVisualized.setPosition(sf::Vector2f(rocketCollisionBox.left, rocketCollisionBox.top));
    rocketColBoxVisualized.setSize(sf::Vector2f(rocketCollisionBox.width, rocketCollisionBox.height));
}

void Rocket::initMoonDebug()
{
    moonColliderVisualized.setFillColor(sf::Color(0, 0, 0, 0));
    moonColliderVisualized.setOutlineColor(sf::Color::Magenta);
    moonColliderVisualized.setOutlineThickness(1.0f);
    moonColliderVisualized.setPosition(sf::Vector2f(moonSprite.getPosition().x - (moonSize.x * 0.5f * moonSprite.getScale().x), moonSprite.getPosition().y - (moonSize.y * 0.5f * moonSprite.getScale().y)));
    moonColliderVisualized.setRadius(25.6f);
}

void Rocket::initRocket()
{
    rocketTexture.setSmooth(true);
    rocketSprite.setTexture(rocketTexture);
    rocketSize = rocketTexture.getSize();
    rocketSprite.setOrigin(0.0f, 0.0f);
    rocketSprite.setPosition(rocketPosition);
    rocketSprite.setRotation(-90.0f);
    rocketSprite.setScale(0.05f, 0.05f);

    // Set an invisible collision box around the rocket sprite
    rocketCollisionBox = sf::FloatRect(rocketSprite.getPosition().x, rocketSprite.getPosition().y, rocketSize.x * 0.05f, rocketSize.y * 0.05f);
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