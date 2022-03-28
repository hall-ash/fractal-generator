output: main.o Bitmap.o Mandelbrot.o FractalGenerator.o Zoom.o
	g++ -Wall -std=c++11 main.o Bitmap.o Mandelbrot.o FractalGenerator.o Zoom.o -o output

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

Bitmap.o: Bitmap.cpp Bitmap.h BitmapFileHeader.h BitmapInfoHeader.h
	g++ -c -std=c++11 Bitmap.cpp

Mandelbrot.o: Mandelbrot.cpp Mandelbrot.h
	g++ -c -std=c++11 Mandelbrot.cpp

FractalGenerator.o: FractalGenerator.cpp FractalGenerator.h RGB.h
	g++ -c -std=c++11 FractalGenerator.cpp

Zoom.o: Zoom.cpp Zoom.h
	g++ -c -std=c++11 Zoom.cpp

clean:
	rm *.o output
