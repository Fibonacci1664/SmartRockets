/*
 * This is the Rocket class and handles: -
 *		- Loading in textures
 *		- Setting up debug and collision boxes
 *		- Updating the rockets position through applying force
 *		- Assessing fitness
 *		- Ensuring velocity doesn't exceed a predefined maximum
 *		- Carrying out collision checks with the target and with the obstacle
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "Rocket.h"
#include <cmath>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
constexpr auto PI = 3.14159265359;

// CONSTRUCTOR / DESTRUCTOR
Rocket::Rocket(sf::RenderWindow* hwnd) : window(hwnd)
{
    distanceToTarget = 0.0f;
    fitnessScore = 0.0f;
    geneCounter = 0;
    maxSpeed = 2.0f;
    speed = 1.2f;
    newRocketXScale = 0.1f;
    newRocketYScale = 0.1f;
    currentRotation = 0.0f;

    hitObstacle = false;

    rocketPosition = sf::Vector2f(640.0f, 600.0f);  
    velocity = sf::Vector2f(0.0f, 0.0f);
    accel = sf::Vector2f(0.0f, 0.0f);

    loadTexture();
    initRocket();

    if (displayDebug)
    {
        initDebug();
    }
}

Rocket::~Rocket()
{
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS
void Rocket::update(float dt, Obstacle* obstacle)
{
    if (!hitObstacle)
    {
        accel = dna.getGene(geneCounter);

        addForce(accel, dt);
        ++geneCounter;

        // Reset the gene indexing
        if (geneCounter == dna.getDNALength())
        {
            geneCounter = 0;
        }

        // Update the rockets invisible collision box
        rocketCollisionBox = sf::FloatRect(rocketSprite.getPosition().x, rocketSprite.getPosition().y, 2.5f, 2.5f);

        // Update the rectangle visualisation of the rockets collision box
        // AABB FloatRect is axis aligned by definition so while the rockets rotate according to their velocity
        // The AABB FloatRect and by extension the RectangleShape to visualise the FloatRect collider does NOT rotate
        // While it would be possible to rotate the RectangleShape this would be completely pointless and purely
        // cosmetic as the AABB FloatRect collider does NOT rotate
        if (displayDebug)
        {
            rocketColBoxVisualized.setPosition(sf::Vector2f(rocketCollisionBox.left, rocketCollisionBox.top));
        }
    }

    hitObstacle = checkObstacleCollisions(obstacle);
    accel *= 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::render()
{
    window->draw(rocketSprite);

    if (displayDebug)
    {
        window->draw(rocketColBoxVisualized);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::assessFitness(Target* target)
{
    float xDir = target->getSprite().getPosition().x - rocketPosition.x;
    float yDir = target->getSprite().getPosition().y - rocketPosition.y;

    //sf::Vector2f dirToTarget = target->getSprite().getPosition() - rocketPosition;
    sf::Vector2f dirToTarget = sf::Vector2f(xDir, yDir);
    distanceToTarget = calculateMagnitude(dirToTarget);
    fitnessScore = std::powf(1 / distanceToTarget, 2);

    // Punish the rockets that hit the obstacle
    if (hitObstacle)
    {
        // Reduce the fitness to decrease the likelyhood of making it to the next generation
        fitnessScore *= 0.1f;

        // A higher magnitude means worse performance as technically the rocket is assesed to be further
        // from the target, therefore, if the rocket hits the obstacle, then set this rockets
        // magnitude to some extremely high arbitrary value.
        distanceToTarget = 1000000.0f;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////

float Rocket::getDistanceToTarget()
{
    return distanceToTarget;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

float Rocket::getFitnessScore()
{
    return fitnessScore;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

DNA Rocket::getDNASequence()
{
    return dna;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// Something is not quite right with this check, it might be related to the collision box however
// rather than this function
bool Rocket::checkItersection(Target* target)
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
    float centreX = target->getDebugCircle().getPosition().x;
    float centreY = target->getDebugCircle().getPosition().y;

    // Find the nearest point on the rectangle to the center of the circle
    int Xnearest = std::max(X1, std::min(centreX, X2));
    int Ynearest = std::max(Y1, std::min(centreY, Y2));

    // Find the distance between the nearest point and the center of the circle
    // distX^2 + distY^2 <= radiius^2
    int distX = Xnearest - centreX;
    int distY = Ynearest - centreY;
    int circleRadius = target->getDebugCircle().getRadius();
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

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::setRocketColliderColour()
{
    rocketColBoxVisualized.setOutlineColor(sf::Color::White);
    rocketSprite.setColor(sf::Color::Green);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

sf::Sprite Rocket::getRocketSprite()
{
    return rocketSprite;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::setDNASequence(DNA newDNA)
{
    dna = newDNA;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////

float Rocket::calculateMagnitude(sf::Vector2f vec)
{
    float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    return mag;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

sf::Vector2f Rocket::limiter()
{
    float tempMag = calculateMagnitude(velocity);
    sf::Vector2f newVel;
    //sf::Vector2f dir = velocity;

    float thetaRad = std::atan2(velocity.y, velocity.x);
    int thetaDeg = (thetaRad * 180) / 3.14159265359f;

    // Test if the magnitude is greater than maxSpeed
    if (tempMag > maxSpeed)
    {
        // Then calc a new vector using the same angle but limited to the max speed
        newVel = sf::Vector2f(maxSpeed * std::cos(thetaRad), maxSpeed * std::sin(thetaRad));
    }
    else
    {
        // If magnitude is less than maxSpeed then just return the current velocity, as it's ok
        return velocity;
    }

    // Otherwise return the new limited velocity
    return newVel;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::addForce(sf::Vector2f newAccel, float dt)
{
    // Normalise
    accel = calculateUnitVector(newAccel);
    // Scale
    accel *= (speed * dt);
    // Add the accel to the velocity
    velocity += accel;
    // Ensure that the velocity is limited to max speed of 10
    velocity = limiter();
    // Update rockets position using velocity
    rocketPosition += velocity;
    // Update the rockets rotation accroding to its velocity
    currentRotation = calculateRotation(velocity);
    // Not sure why I need to -90 to get the sprite to be rotated correctly, think it's to do with
    // the fact the the unit circle 0 deg starts at the East pos, and the rotation for SFML 0 deg starts a the North pos, not sure though??
    currentRotation -= 90;
    // Set new rocket position
    rocketSprite.setPosition(rocketPosition);
    rocketSprite.setRotation(currentRotation);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

float Rocket::calculateRotation(sf::Vector2f vel)
{
    sf::Vector2f dir = -vel;

    float thetaRad = std::atan2(dir.y, dir.x);
    int thetaDeg = (thetaRad * 180) / 3.14159265359f;

    return thetaDeg;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::initDebug()
{
    initRocketDebug();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::initRocketDebug()
{
    rocketColBoxVisualized.setFillColor(sf::Color(0, 0, 0, 0));
    rocketColBoxVisualized.setOutlineColor(sf::Color::Magenta);
    rocketColBoxVisualized.setOutlineThickness(1.0f); 
    rocketColBoxVisualized.setPosition(sf::Vector2f(rocketCollisionBox.left, rocketCollisionBox.top));
    rocketColBoxVisualized.setSize(sf::Vector2f(2.5f, 2.5f));  
}

//////////////////////////////////////////////////////////////////////////////////////////////////

bool Rocket::checkObstacleCollisions(Obstacle* obstacle)
{
    if (rocketCollisionBox.intersects(obstacle->getCollisonBox()))
    {
        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::initRocket()
{
    rocketTexture.setSmooth(true);
    rocketSprite.setTexture(rocketTexture);
    rocketSize = rocketTexture.getSize();
    
    // Origin top centre, thrust would normally come from the btm centre, however due to issues with using AABB and not OBB
    // I struglled to move the collider according to how much the rocket rotated by its change in x,y as of course
    // AABB colliders do not rotate by definition, so trying to move the collider to the tip of the rocket every frame
    // became a bit of a problem, so left it at this solution for the time being, needs OBB though
    rocketSprite.setOrigin(rocketSprite.getPosition().x + rocketSize.x * 0.5f, rocketSprite.getPosition().y);
    rocketSprite.setScale(newRocketXScale, newRocketYScale);
    rocketSprite.setPosition(rocketPosition);
    
    // Set an invisible collision box around the rocket sprite
    rocketCollisionBox = sf::FloatRect(rocketSprite.getPosition().x - 2.0f, rocketSprite.getPosition().y - 37.8f, 2.5f, 2.5f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Rocket::loadTexture()
{
    if (!rocketTexture.loadFromFile("res/sprites/rocket_2.png"))
    {
        std::cout << "Error loading rocket texture\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////