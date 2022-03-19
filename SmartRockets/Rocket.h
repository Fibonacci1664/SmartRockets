#pragma once
#include "DNA.h"
#include <SFML/Graphics.hpp>
#include "Target.h"

class Rocket
{
public:
    Rocket(sf::RenderWindow* hwnd);
    ~Rocket();

    void update(float dt);
    void render();

    void assessFitness();

    // Getters / Setters
    float getMagnitude();
    float getFitnessScore();   
    void setDNASequence(DNA newDNA);
    DNA getDNASequence();
    bool checkItersection();
    void setRocketColliderColour();
    sf::Sprite getRocketSprite();

private:
    sf::Vector2f limiter(float topSpeed);  
    sf::Vector2f calculateUnitVector(sf::Vector2f vec);
    float calculateMagnitude(sf::Vector2f vec);
    float calculateRotation(sf::Vector2f cartesianVec);
    void addForce(sf::Vector2f newForce, float dt);
    void initRocket();
    void initTarget();
    void initDebug();
    void initRocketDebug();
    
    void loadTexture();

    sf::RenderWindow* window;
    sf::Texture rocketTexture;
    sf::Sprite rocketSprite;
    
    // Debug box for rocketmoonColliderVisualized
    sf::RectangleShape rocketColBoxVisualized;
    sf::FloatRect rocketCollisionBox;
    
    Target* target;

    float distanceToTarget;
    float fitnessScore;
    float magnitude;
    float newRocketXScale;
    float newRocketYScale;
    float maxSpeed;
    float speed;
    float currentRotation;

    int geneCounter;
    DNA dna;

    sf::Vector2f rocketPosition;
    
    sf::Vector2f velocity;
    sf::Vector2f accel;
    sf::Vector2u rocketSize;  
};