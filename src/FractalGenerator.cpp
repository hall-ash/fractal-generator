#include "FractalGenerator.h"

FractalGenerator::FractalGenerator(int width, int height, int maxIterations) :
	width(width), height(height), maxIterations(maxIterations), 
	fractalBmp(width, height), zoom(width, height, 2.0 / height), customColorRanges(false)
{
	totalPixels = width * height;
	numIterations = new int[totalPixels];

	hue[RED] = new uint8_t[totalPixels]; 
	hue[GREEN] = new uint8_t[totalPixels]; 
	hue[BLUE] = new uint8_t[totalPixels]; 

	iterationFreq = new int[maxIterations]; 
}

FractalGenerator::~FractalGenerator()
{
	delete[] iterationFreq;
	iterationFreq = nullptr; 

	delete[] numIterations;
	numIterations = nullptr;

	for ( int color = 0; color < COLORS; ++color )
	{
		delete[] hue[color];
		hue[color] = nullptr;
	}

	for ( int range = 0; range < rgbRanges.size(); ++range )
	{
		delete rgbRanges[range];
		rgbRanges[range] = nullptr; 
	}
}

void FractalGenerator::draw()
{
	calculateIterationCount(); 
    determineHues();
	colorFractal();
}

void FractalGenerator::zoomIn(int x, int y, double scale)
{
	zoom.zoomOnPoint(Zoom::Point(x, y), scale);
}

bool FractalGenerator::writeBitmap(const std::string& outputFile)
{
	return fractalBmp.write(outputFile);
}

bool FractalGenerator::validColor(uint8_t color) const
{
	return color >= MIN_INTENSITY && color <= MAX_INTENSITY;
}

int FractalGenerator::getIterationCount(const int pixel) const
{
	if ( pixel >= 0 && pixel < totalPixels )
	{
		return numIterations[pixel];
	}
	
	std::cerr << "error getIterationCount: invalid pixel" << "\n";
	return -1; 
	
}

void FractalGenerator::calculateIterationCount()
{

   	int iterations = 0; 
   	int pixel = 0; 
   	std::complex<double> c(0, 0); 

   	// get cReal and cImag from x, y bitmap coordinates 
   	for ( int y = 0; y < height; ++y )
   	{
   		for (int x = 0; x < width; ++x )
   		{
   			c = zoom.getZoomedComplexCoord(x, y); 
   				
   			iterations = Mandelbrot::getIterations(c);

   			pixel = x + y * width;
   			numIterations[pixel] = iterations; 

   			if ( iterations < maxIterations )
   			{
   				//iterationFreq[iterations] += 1.0 / totalPixels; 
   				++iterationFreq[iterations];
   			}
   		}
   	}
   	
}


void FractalGenerator::determineHues()
{

	// make default color green if no custom color ranges provided
	RGB startColor {0, 0, 0};
	RGB endColor {0, 255, 0}; 
	

	// if custom color ranges were added, calculate number of pixels in each range
	if ( customColorRanges ) getPixelsInRange();

	int iterations = 0;

   	for ( int pixel = 0; pixel < totalPixels; pixel++ )
   	{
   		iterations = numIterations[pixel];
 
   		if ( iterations < maxIterations ) 
   		{
   			double intensityFactor = INTENSITY_FACTOR; //default value 

	   		if ( customColorRanges )
	   		{
	   			int range = getRange(iterations);
				startColor = rgbRanges.at(range)->startRGB;
	   			endColor = rgbRanges.at(range)->endRGB;
	   			intensityFactor = totalPixels / rangeTotals.at(range);
	   		}

    		double intensity = getIntensity(iterations, intensityFactor); 
			setPixelHues(pixel, startColor, endColor, intensity); 	
   		}	
   		else 
   		{
   			// set pixels with maxIterations to black 
   			setPixelHues(pixel, RGB(0,0,0), RGB(0,0,0), 1);
   		}
   	}

}


int FractalGenerator::getRange(const int iterations) const
{
	if ( rgbRanges.size() < 1 ) 
	{
		std::cerr << "Error getRange: rgbRanges is empty\n";
		return -1; 
	}

	for ( int range = 0; range < rgbRanges.size(); ++range )
	{
		int rangeEndIterations = rgbRanges.at(range)->rangeEnd * maxIterations;
		if ( rangeEndIterations > iterations )
			return range;
	}

	std::cerr << "Error getRange\n";
	return -1; 
}


void FractalGenerator::setPixelHues(const int pixel, 
	const RGB& startColor, const RGB& endColor, const double intensity) 
{
	RGB colorDiff = endColor - startColor; 

	hue[RED][pixel] = pow(startColor.red, intensity) + pow(colorDiff.red, intensity); 
	hue[GREEN][pixel] = pow(startColor.green, intensity) + pow(colorDiff.green, intensity); 
	hue[BLUE][pixel] = pow(startColor.blue, intensity) + pow(colorDiff.blue, intensity); 
}

void FractalGenerator::colorFractal()
{
   	Bitmap::BitmapIterator pixelHue = fractalBmp.begin();
   	Bitmap::BitmapIterator bitmapEnd = fractalBmp.end();

	for (int color = 0; pixelHue != bitmapEnd; ++pixelHue, ++color )
    {	
       *pixelHue = hue[color % COLORS][color / COLORS];
    }

}

double FractalGenerator::getIntensity(const int iterations, const double intensityFactor) const
{
	double intensity = 0;
	for ( int iteration = 0; iteration <= iterations; iteration++ )
	{
		// increases intensity in proportion with number of pixels 
		intensity += (double) iterationFreq[iteration] / totalPixels;
	}
	return intensity * intensityFactor; 
}


void FractalGenerator::addColorRange(const RGB& startRGB, const RGB& endRGB, const double rangeEnd)
{
	if ( rangeEnd <= 0.0 || rangeEnd > 1.0 ) 
	{
		std::cerr << "Error addColorRange: check valid rangeEnd\n";
		return;
	}

	double prevRangeEnd = 0; 
	if ( rgbRanges.size() > 0 )
	{
		prevRangeEnd = rgbRanges[rgbRanges.size() - 1]->rangeEnd;

		if ( rangeEnd <= prevRangeEnd )
		{
			std::cerr << "Error addColorRange: ensure rangeEnd is greater than than"
				<< "the previously added rangEnd\n";
			return;
		}
	}

	RGBRange* newRange = new RGBRange{startRGB, endRGB, rangeEnd};

	rgbRanges.push_back(newRange);

	if ( !customColorRanges ) customColorRanges = true;
}


void FractalGenerator::getPixelsInRange() 
{

	int iterMin = 0;
	int iterMax = 0;
	
	for ( int range = 0; range < rgbRanges.size(); ++range )
	{
		if ( range > 0 ) iterMin = rgbRanges[range - 1]->rangeEnd * maxIterations;
		iterMax = rgbRanges[range]->rangeEnd * maxIterations;

		int pixelsInRange = 0;
		for ( int iter = iterMin; iter < iterMax; ++iter )
		{
			pixelsInRange += iterationFreq[iter];
		}
		rangeTotals.push_back(pixelsInRange);

	}
}


