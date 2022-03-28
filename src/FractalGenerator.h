#ifndef FRACTAL_GENERATOR_H
#define FRACTAL_GENERATOR_H

#include <iostream>
#include <math.h>
#include <complex>
#include <vector>
#include "Zoom.h"
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "RGB.h"

class FractalGenerator
{
	const static int COLORS = 3;
	const static int MIN_INTENSITY = 0;
	const static int MAX_INTENSITY = 255;
	constexpr static double INTENSITY_FACTOR = 1.3;
	
public:
	// struct Hue {
	// 	uint8_t red{0};
	// 	uint8_t green{0};
	// 	uint8_t blue{0};

	// 	Hue(red, green, blue) 
	// 		: red(red), green(green), blue(blue) {};
	// };

	struct RGBRange {
		RGB startRGB;
		RGB endRGB;
		double rangeEnd;

		RGBRange(const RGB& startRGB, 
			const RGB& endRGB, const double rangeEnd) :
		startRGB(startRGB), endRGB(endRGB), rangeEnd(rangeEnd) {};
	};

	FractalGenerator(int width, int height, int maxIterations);
	virtual ~FractalGenerator();

	void draw(); 
	void zoomIn(int x, int y, double scale);
	void addColorRange(const RGB& startRGB, const RGB& endRGB, const double rangeEnd);
	bool writeBitmap(const std::string& outputFile);

	// void calculateRangeTotals();

private:
	// bitmap dimensions
	int width{0};
	int height{0};

	// number of pixels in bitmap
	int totalPixels{0}; 

	// max number of iterations to execute before algorithm cutoff
	int maxIterations{0}; 

	// number of pixels for a given iteration count
	int* iterationFreq{nullptr};

	// number of iterations for a given pixel
	int* numIterations{nullptr};

	// pixel hue
	uint8_t* hue[COLORS]; 

	//Hue* pixelHues{nullptr};

	enum { BLUE, GREEN, RED }; 

	Bitmap fractalBmp; 
	
	Zoom zoom; 

	bool customColorRanges;

	//std::vector<int> ranges;
	//std::vector<RGB> colors;
	std::vector<RGBRange*> rgbRanges; 
	std::vector<int> rangeTotals; 

	bool validColor(uint8_t color) const; 
	//int getIterationCount(const int pixel) const; 
	void calculateIterationCount(); 
	void determineHues(); 
	void colorFractal();
	double getIntensity(const int iterations, const double intensityFactor) const;
	int getIterationCount(const int pixel) const;
	void setPixelHues(const int pixel, const RGB& startColor, const RGB& endColor, const double intensityFactor); 
	void getPixelsInRange();
	int getRange(const int iterations) const;


};

#endif // FRACTAL_GENERATOR_H