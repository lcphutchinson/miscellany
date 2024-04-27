#pragma once
#include <string>

/**
 * Simple Object representation of a rational fraction.
 *
 */
class Fraction
{
public:
	int numerator;
	int denominator;
	Fraction(int in_numerator, int in_denominator);

	//IO Methods
	double toDouble();	
	std::string toString();
};

// Helper Methods
int gcd(int a, int b);
int lcm(int a, int b);

// Operations
Fraction *sum(Fraction *f1, Fraction *f2);
Fraction *sum(Fraction *f, int n);
Fraction *sum(int n, Fraction *f);

Fraction *difference(Fraction *f1, Fraction *f2);
Fraction *difference(Fraction *f, int n);
Fraction *difference(int n, Fraction *f);

Fraction *product(Fraction *f1, Fraction *f2);
Fraction *product(Fraction *f, int n);
Fraction *product(int n, Fraction *f);

Fraction *quotient(Fraction *f1, Fraction *f2);
Fraction *quotient(Fraction *f, int n);
Fraction *quotient(int n, Fraction *f);

Fraction *inverse(Fraction *f);

