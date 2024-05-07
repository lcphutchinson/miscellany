#pragma once
#include <string>
#include "fraction.h"

Fraction::Fraction(int in_numerator, int in_denominator = 1)
{
	int divisor = gcd(in_numerator, in_denominator);
	numerator = in_numerator/divisor;
	denominator = in_denominator/divisor;
	if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
}

double Fraction::toDouble()
{
	return (double)numerator / denominator;
}

std::string Fraction::toString()
{
	if(denominator == 1) return "(" + std::to_string(numerator) + ")";
	else return "(" + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";
}

int gcd(int a, int b)
{
	if(b == 0) return a;
	else return gcd(b, a % b);
}

int lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}

Fraction *sum(Fraction *f1, Fraction *f2)
{
	int commonDenominator = lcm(f1->denominator, f2->denominator);

	int operand1 = (commonDenominator / f1->denominator) * f1->numerator;
	int operand2 = (commonDenominator / f2->denominator) * f2->numerator;
	int sum = operand1 + operand2;
	return new Fraction(sum, commonDenominator);
}

Fraction *sum(Fraction *f, int n)
{
	return sum(f, new Fraction(n));
}

Fraction *sum(int n, Fraction *f)
{
	return sum(new Fraction(n), f);
}

Fraction *difference(Fraction *f1, Fraction *f2)
{
	int commonDenominator = lcm(f1->denominator, f2->denominator);
	
	int operand1 = (commonDenominator / f1->denominator) * f1->numerator;
	int operand2 = (commonDenominator / f2->denominator) * f2->numerator;
	int difference = operand1 - operand2;
	return new Fraction(difference, commonDenominator);
}

Fraction *difference(Fraction *f, int n)
{
	return difference(f, new Fraction(n));
}

Fraction *difference(int n, Fraction *f)
{
	return difference(new Fraction(n), f);
}

Fraction *product(Fraction *f1, Fraction *f2)
{
	int newNumerator = f1->numerator * f2->numerator;
	int newDenominator = f1->denominator * f2->denominator;
	return new Fraction(newNumerator, newDenominator);
}

Fraction *product(Fraction *f, int n)
{
	return product(f, new Fraction(n));
}

Fraction *product(int n, Fraction *f)
{
	return product(new Fraction(n), f);
}

Fraction *quotient(Fraction *f1, Fraction *f2)
{
	int newNumerator = f1->numerator * f2->denominator;
	int newDenominator = f1->denominator * f2->numerator;
	return new Fraction(newNumerator, newDenominator);
}

Fraction *quotient(Fraction *f, int n)
{
	return quotient(f, new Fraction(n));
}

Fraction *quotient(int n, Fraction *f)
{
	return quotient(new Fraction(n), f);
}

Fraction *invert(Fraction *f)
{
	return new Fraction(f->denominator, f->numerator);
}	
