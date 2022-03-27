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
#pragma once
#include "DNA.h"
#include "Target.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
extern bool displayDebug;

//////////////////////////////////////////////////////////////////////////////////////////////////

class Rocket
{
public:
    Rocket(sf::RenderWindow* hwnd);
    ~Rocket();

    void update(float dt, Obstacle* obstacle);
    void render();

    void assessFitness(Target* target);
    bool checkItersection(Target* target);

    // Getters / Setters
    float getDistanceToTarget();
    float getFitnessScore();   
    void setDNASequence(DNA newDNA);
    DNA getDNASequence();
    void setRocketColliderColour();
    sf::Sprite getRocketSprite();

private:
    sf::Vector2f limiter();  
    sf::Vector2f calculateUnitVector(sf::Vector2f vec);
    float calculateMagnitude(sf::Vector2f vec);
    float calculateRotation(sf::Vector2f vel);
    void addForce(sf::Vector2f newForce, float dt);
    bool checkObstacleCollisions(Obstacle* obstacle);

    void initRocket();
    void initDebug();
    void initRocketDebug();   
    void loadTexture();

    sf::RenderWindow* window;
    sf::Texture rocketTexture;
    sf::Sprite rocketSprite;
    sf::Vector2f rocketPosition;
    sf::Vector2f velocity;
    sf::Vector2f accel;
    sf::Vector2u rocketSize;
    
    // Debug box for rocketmoonColliderVisualized
    sf::RectangleShape rocketColBoxVisualized;
    sf::FloatRect rocketCollisionBox;

    DNA dna;

    bool hitObstacle;

    int geneCounter;

    float distanceToTarget;
    float fitnessScore;
    float newRocketXScale;
    float newRocketYScale;
    float maxSpeed;
    float speed;
    float currentRotation;
};

//////////////////////////////////////////////////////////////////////////////////////////////////