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

    float getMagnitude();
    float getFitnessScore();
    DNA getDNASequence();
    void setDNASequence(DNA newDNA);

private:
    sf::Vector2f limiter(float topSpeed);
    float calculateMagnitude(sf::Vector2f vec);
    sf::Vector2f calculateUnitVector(sf::Vector2f vec);
    void addForce(sf::Vector2f newForce, float dt);
    void initTarget();
    void initRocket();
    void loadTextures();

    sf::RenderWindow* window;
    sf::Texture rocketTexture;
    sf::Sprite rocketSprite;
    sf::Texture moonTexture;
    sf::Sprite moonSprite;
    float distanceToTarget = 0.0f;
    DNA dna;
    float fitnessScore = 0.0f;
    float magnitude = 0.0f;
    int geneCounter = 0;
    float maxSpeed = 10.0f;
    float speed = 2.0f;
    float mass = 1.0f;
    sf::Vector2f rocketPosition;
    sf::Vector2f moonPosition;
    sf::Vector2f velocity;
    sf::Vector2f accel;
    sf::Vector2u rocketSize;
    sf::Vector2u moonSize;
};

