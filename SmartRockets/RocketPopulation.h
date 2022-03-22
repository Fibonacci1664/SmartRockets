#pragma once
#include <vector>
#include "Rocket.h"
#include "Target.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>

extern int POPULATION_SIZE;

class RocketPopulation
{
public:
    RocketPopulation(sf::RenderWindow* hwnd);
    ~RocketPopulation();

    void update(float dt, Obstacle* obstacle);
    void render();
    
    double mapRange(double a1, double a2, double b1, double b2, double s);
    double getTotalFitness();
    Rocket* determineBestRocket();
    void clearMatingPool();
    void fitness(Target* target);
    bool selection(Target* target);
    void reproduction();
    int getGeneration();
    int getMatingPoolSize();

private:
    void initPopulation();  
    bool populateMatingPool();

    Rocket* child;
    DNA parentA_DNA;
    DNA parentB_DNA;
    DNA childDNA;

    sf::RenderWindow* window;
    std::vector<Rocket*> rockets;
    std::vector<Rocket> matingPool;

    int generation;
    int bestIndex;
};