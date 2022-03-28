#include <complex>
#include <cmath>
#include <iostream>
#include "Mandelbrot.h"


Mandelbrot::Mandelbrot()
{

}

Mandelbrot::~Mandelbrot()
{

}

// Zn+1 = (Zn)^2 + c
// start at z0 = 0
// c is point on graph
// keep applying equation until |z| > 2 or maxiterations 
int Mandelbrot::getIterations(std::complex<double> c)
{
	std::complex<double> Zn (0, 0);
	int iterations = 0; 

	// if abs( Zn ) <= 2 then Zn is in Mandelbrot set
	while ( iterations < MAX_ITERATIONS )
	{
		Zn = Zn * Zn + c;

		if ( abs(Zn) > 2 ) break; 

		iterations++;
	}

	return iterations; // if reached MAX_ITERATIONS, Zn is in set
}