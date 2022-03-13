#pragma once
#include "DNA.h"
#include <SFML/Graphics.hpp>

class Rocket
{
public:
    Rocket(sf::RenderWindow* hwnd, sf::CircleShape target);
    ~Rocket();

    void update(float dt);
    void render();

    void assessFitness();
    void run();
    float getFitnessScore();
    DNA getDNASequence();
    void setDNASequence(DNA newDNA);

private:
    void addForce(sf::Vector2f newForce);
    void initRocket();
    void loadTexture();

    sf::RenderWindow* window;
    sf::CircleShape theTarget;
    sf::Texture rocketTexture;
    sf::Sprite rocketSprite;
    float distanceToTarget = 0.0f;
    DNA dna;
    float fitnessScore = 0.0f;
    int geneCounter = 0;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2u size;
};

