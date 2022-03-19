#pragma once
#include "DNA.h"
#include <SFML/Graphics.hpp>

class Rocket
{
public:
    Rocket(sf::RenderWindow* hwnd);
    ~Rocket();

    void update(float dt);
    void render();

    sf::Vector2f lerp(sf::Vector2f v1, sf::Vector2f v2, float dt);
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
    void initTarget();
    void initRocket();
    void initDebug();
    void initRocketDebug();
    void initMoonDebug();
    void loadTextures();

    sf::RenderWindow* window;
    sf::Texture rocketTexture;
    sf::Sprite rocketSprite;
    sf::Texture moonTexture;
    sf::Sprite moonSprite;

    // Debug box for rocketmoonColliderVisualized
    sf::RectangleShape rocketColBoxVisualized;
    sf::FloatRect rocketCollisionBox;
    
    // Debug circle for moon
    sf::CircleShape moonColliderVisualized;

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
    sf::Vector2f moonPosition;
    sf::Vector2f velocity;
    sf::Vector2f accel;
    sf::Vector2u rocketSize;
    sf::Vector2u moonSize;
};