#pragma once
#include <vector>
#include "Rocket.h"
#include <SFML/Graphics.hpp>

const int POPULATION_SIZE = 50;

class RocketPopulation
{
public:
    RocketPopulation(sf::RenderWindow* hwnd);
    ~RocketPopulation();

    void update(float dt);
    void render();
    void beginDraw();
    void endDraw();
    double mapRange(double a1, double a2, double b1, double b2, double s);
    double getTotalFitness();
    Rocket* determineBestRocket();
    void clearMatingPool();
    void fitness();
    void selection();
    void reproduction();

private:
    void initPopulation();  
    void populateMatingPool();

    Rocket* closestRocket;

    sf::RenderWindow* window;
    std::vector<Rocket*> rockets;
    std::vector<Rocket> matingPool;
};