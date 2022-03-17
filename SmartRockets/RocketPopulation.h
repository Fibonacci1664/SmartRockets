#pragma once
#include <vector>
#include "Rocket.h"
#include <SFML/Graphics/CircleShape.hpp>

const int POPULATION_SIZE = 100;

class RocketPopulation
{
public:
    RocketPopulation(sf::RenderWindow* hwnd);
    ~RocketPopulation();

    void update(float dt);
    void render();
    void beginDraw();
    void endDraw();
    float determineBestRocket();
    void clearMatingPool();
    void fitness();
    void selection();
    void reproduction();

private:
    void initPopulation();  
    void populateMatingPool();

    sf::RenderWindow* window;
    std::array<Rocket*, POPULATION_SIZE> rockets;
    std::vector<Rocket*> matingPool;
};

