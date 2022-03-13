#include "Rocket.h"
#include <cmath>
#include <iostream>

Rocket::Rocket(sf::RenderWindow* hwnd, sf::CircleShape target) : window(hwnd)
{
    position = sf::Vector2f(0.0f, 0.0f);
    velocity = sf::Vector2f(0.0f, 0.0f);
    theTarget = target;

    initRocket();
}

Rocket::~Rocket()
{

}

void Rocket::update(float dt)
{
    sf::Vector2f geneVector = dna.getGene(geneCounter);
    addForce(geneVector);
    ++geneCounter;
}

void Rocket::render()
{
    window->draw(rocketSprite);
}

void Rocket::assessFitness()
{
    sf::Vector2f dirToTarget = theTarget.getPosition() - position;
    float magnitude = std::sqrt(dirToTarget.x * dirToTarget.x + dirToTarget.y * dirToTarget.y);
    fitnessScore = std::powf(1 / magnitude, 2);
}

void Rocket::run()
{
    
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

void Rocket::addForce(sf::Vector2f newForce)
{
    position.x += newForce.x;
    position.y += newForce.y;
}

void Rocket::initRocket()
{
    loadTexture();
    rocketTexture.setSmooth(true);
    rocketSprite.setTexture(rocketTexture);
    size = rocketTexture.getSize();
    rocketSprite.setOrigin(size.x * 0.5f, size.y - 50);
    //collisionBox = sf::FloatRect(asteroidSprite.getPosition().x - size.x * 0.5f, asteroidSprite.getPosition().y - size.y * 0.5f, size.x, size.y);
}

void Rocket::loadTexture()
{
    if (!rocketTexture.loadFromFile("res/RocketSprite.png"))
    {
        std::cout << "Error loading asteroid texture\n";
    }
}