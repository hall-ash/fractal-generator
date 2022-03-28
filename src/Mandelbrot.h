#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>

class Mandelbrot
{
public:
	Mandelbrot();
	virtual ~Mandelbrot();

	static const int MAX_ITERATIONS = 1000; // more iterations = better quality image

	static int getIterations(std::complex<double> c);
};

#endif // MANDELBROT_H