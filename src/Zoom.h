#ifndef ZOOM_H
#define ZOOM_H

#include <vector>
#include <iostream>
#include <complex>

class Zoom 
{
public:
	struct Point
	{
		double x{0};
		double y{0};
		//double magnify{0};
		Point(double x, double y): x(x), y(y) {};
		//Point(double x, double y, double magnify): x(x), y(y), magnify(magnify) {};

		friend std::ostream& operator<<(std::ostream& out, const Point& point)
		{
			//if ( point.magnify == 0 )
				out << "(" << point.x << ", " << point.y << ")";
			// else
			// 	out << point.magnify << "X: " << point.x << ", " << point.y;
			return out;
		};
		
	};

	Zoom(const int imgWidth, const int imgHeight); 
	Zoom(const int imgWidth, const int imgHeight, double scale); 
	//Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {};
	virtual ~Zoom(); 

	void zoomOnPoint(const Point& point, const double newScale);
	std::complex<double> getZoomedComplexCoord(int x, int y); 


private:
	// image dimensions
	int imgWidth{0};
	int imgHeight{0};

	// original center
	Point imgCenter{0, 0};

	// new center after zooming
	Point zoomedCenter{0, 0};

	double scale{1.0}; 

	std::vector<Point> zoomHistory; 

	void setImageCenter(); 

};

#endif // ZOOM_H