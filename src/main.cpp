#include <cstdint>
#include <iostream>
#include <string>
#include "FractalGenerator.h"
#include "RGB.h"

#define DRAW_FRACTAL 1


int main() 
{
	// bitmap image dimensions 
	const int WIDTH = 800;
	const int HEIGHT = 600;
	
	std::string outputFile{"fractal.bmp"};

	FractalGenerator fractal{WIDTH, HEIGHT, Mandelbrot::MAX_ITERATIONS}; 

	fractal.zoomIn(234, 308, 0.99); 
	
	if ( DRAW_FRACTAL )
	{

		std::cout << "Creating fractal...\n";
   		
		fractal.draw();

		if ( fractal.writeBitmap(outputFile) )
		{
			std::cout << "Saved to file \"" << outputFile << "\"\n";
		}
		else
		{
			std::cerr << "Error writing to bitmap\n";
		}
	}

	return 0;
}