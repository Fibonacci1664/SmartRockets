#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>

const int DNA_LENGTH = 20;
extern int MUTATION_RATE;

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

	int DNAlength;
	std::array<sf::Vector2f, DNA_LENGTH> genes;
	float maxForce;
};