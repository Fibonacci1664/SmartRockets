#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>

const int DNA_LENGTH = 10;

class DNA
{
public:
	DNA();
	~DNA();

	void mutate();
	DNA crossover(DNA partner);
	sf::Vector2f getGene(int indexPos);

private:
	void createDNAstrand();
	sf::Vector2f getRandom2DVector();

	int DNAlength = 10;
	int mutationRate = 1;
	std::array<sf::Vector2f, DNA_LENGTH> genes;
	float maxForce = 0.1f;
};

