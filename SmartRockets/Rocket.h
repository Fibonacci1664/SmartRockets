#pragma once
#include "DNA.h"
#include "Target.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>

extern bool displayDebug;

class Rocket
{
public:
    Rocket(sf::RenderWindow* hwnd);
    ~Rocket();

    void update(float dt, Obstacle* obstacle);
    void render();

    void assessFitness(Target* target);

    // Getters / Setters
    float getMagnitude();
    float getFitnessScore();   
    void setDNASequence(DNA newDNA);
    DNA getDNASequence();
    bool checkItersection(Target* target);
    void setRocketColliderColour();
    sf::Sprite getRocketSprite();

private:
    sf::Vector2f limiter(float topSpeed);  
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
    
    // Debug box for rocketmoonColliderVisualized
    sf::RectangleShape rocketColBoxVisualized;
    sf::FloatRect rocketCollisionBox;

    float distanceToTarget;
    float fitnessScore;
    float magnitude;
    float newRocketXScale;
    float newRocketYScale;
    float maxSpeed;
    float speed;
    float currentRotation;

    bool hitObstacle;

    int geneCounter;
    DNA dna;

    sf::Vector2f rocketPosition;
    
    sf::Vector2f velocity;
    sf::Vector2f accel;
    sf::Vector2u rocketSize;  
};