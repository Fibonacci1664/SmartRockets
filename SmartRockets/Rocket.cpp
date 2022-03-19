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
    speed = 0.4f;
    newRocketXScale = 0.04f;
    newRocketYScale = 0.04f;
    currentRotation = 0.0f;

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
    rocketCollisionBox = sf::FloatRect(rocketSprite.getPosition().x, rocketSprite.getPosition().y, rocketSize.x * newRocketXScale, rocketSize.y * newRocketYScale);
    rocketColBoxVisualized.setRotation(currentRotation);

    // Update the rectangle visualisation of the rockets collision box
    rocketColBoxVisualized.setPosition(sf::Vector2f(rocketCollisionBox.left, rocketCollisionBox.top));
    rocketColBoxVisualized.setRotation(currentRotation);
}

void Rocket::render()
{
    window->draw(rocketColBoxVisualized);
    window->draw(moonColliderVisualized);
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

bool Rocket::checkItersection()
{
    // Set up variables to represent the rect
    // Left
    float X1 = rocketCollisionBox.left;
    // Right
    float X2 = rocketCollisionBox.left + rocketCollisionBox.width;
    // Btm
    float Y1 = rocketCollisionBox.top + rocketCollisionBox.height;
    // Top
    float Y2 = rocketCollisionBox.top;

    // Set up variables to represent the circle target
    float centreX = moonColliderVisualized.getPosition().x + moonSize.x * 0.5 * moonSprite.getScale().x;
    float centreY = moonColliderVisualized.getPosition().y + moonSize.y * 0.5 * moonSprite.getScale().y;

    // Find the nearest point on the rectangle to the center of the circle
    int Xnearest = std::max(X1, std::min(centreX, X2));
    int Ynearest = std::max(Y1, std::min(centreY, Y2));

    // Find the distance between the nearest point and the center of the circle
    // distX^2 + distY^2 <= radiius^2
    int distX = Xnearest - centreX;
    int distY = Ynearest - centreY;
    int circleRadius = moonColliderVisualized.getRadius();
    int radSquared = circleRadius * circleRadius;
    int xSquared = distX * distX;
    int ySquared = distY * distY;
    int distSquared = xSquared + ySquared;

    // Check for intersection
    if (distSquared <= radSquared)
    {
        return true;
    }

    return false;
}

void Rocket::setRocketColliderColour()
{
    rocketColBoxVisualized.setOutlineColor(sf::Color::White);
    rocketSprite.setColor(sf::Color::Green);
    //rocketSprite.setScale(0.06f, 0.06f);
}

sf::Sprite Rocket::getRocketSprite()
{
    return rocketSprite;
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
    accel *= speed;
    // Add the accel to the velocity
    velocity += accel * dt;
    // Ensure that the velocity is limited to max magnitude of 10
    velocity = limiter(maxSpeed);
    // Update rockets position using velocity
    rocketPosition += velocity;  
    // Update the rockets rotation accroding to its velocity
    currentRotation = calculateRotation(velocity);
    rocketSprite.setRotation(currentRotation);
    // Set new rocket position
    rocketSprite.setPosition(rocketPosition);
}

float Rocket::calculateRotation(sf::Vector2f cartesianVec)
{
    // Get the direction of the velocity vector
    float thetaRad = std::atan2f(cartesianVec.y, cartesianVec.x);
    int thetaDeg = (thetaRad * 180) / 3.14159265359f;

    return thetaDeg;
}

void Rocket::initTarget()
{
    moonTexture.setSmooth(true);
    moonSprite.setTexture(moonTexture);
    moonSize = moonTexture.getSize();
    moonSprite.setOrigin(moonSize.x * 0.5f, moonSize.y * 0.5f);
    moonSprite.setScale(0.1f, 0.1f);
    moonSprite.setPosition(moonPosition); 
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
    moonColliderVisualized.setRadius(12.8f);
    moonColliderVisualized.setOrigin(sf::Vector2f(12.8f, 12.8f));
    moonColliderVisualized.setPosition(sf::Vector2f(moonSprite.getPosition().x, moonSprite.getPosition().y));  
}

void Rocket::initRocket()
{
    rocketTexture.setSmooth(true);
    rocketSprite.setTexture(rocketTexture);
    rocketSize = rocketTexture.getSize();
    rocketSprite.setOrigin(0.0f, 0.0f);
    rocketSprite.setRotation(-90.0f);    
    rocketSprite.setScale(newRocketXScale, newRocketYScale);
    rocketSprite.setPosition(rocketPosition);
    
    // Set an invisible collision box around the rocket sprite
    rocketCollisionBox = sf::FloatRect(rocketSprite.getPosition().x, rocketSprite.getPosition().y, rocketSize.x * newRocketXScale, rocketSize.y * newRocketYScale);
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