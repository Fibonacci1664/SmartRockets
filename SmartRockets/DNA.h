/*
 * This is the DNA class and handles: -
 *		- Maintaining a collection of 2D vectors known as genes
 *		- Mutating the gene strand
 *		- Crossing over 1 parents DNA with another to create a new DNA strand
 *
 * Original @author D. Green.
 *
 * © D. Green. 2022.
 */

//////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#pragma once
#include <array>
#include <SFML/System/Vector2.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBALS
const int DNA_LENGTH = 660;
extern int MUTATION_RATE;

//////////////////////////////////////////////////////////////////////////////////////////////////

class DNA
{
public:
	DNA();
	~DNA();

	void mutate();
	DNA crossover(DNA partner);
	sf::Vector2f getGene(int indexPos);
	const int getDNALength();

private:
	void createDNAstrand();
	sf::Vector2f getRandom2DVector();

	std::array<sf::Vector2f, DNA_LENGTH> genes;

	int DNAlength;
	
	float maxForce;
};

//////////////////////////////////////////////////////////////////////////////////////////////////