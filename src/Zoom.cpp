#include "Zoom.h"

Zoom::Zoom(const int imgWidth, const int imgHeight) : imgWidth(imgWidth), imgHeight(imgHeight)
{
	setImageCenter();
}

Zoom::Zoom(const int imgWidth, const int imgHeight, double magnification) : imgWidth(imgWidth), imgHeight(imgHeight)
{
	setImageCenter();
	zoomOnPoint(Zoom::Point(imgCenter.x, imgCenter.y), magnification); 
}

Zoom::~Zoom()
{
	
}

void Zoom::zoomOnPoint(const Point& point, const double newScale)
{
	zoomHistory.push_back(point); 

	zoomedCenter.x += (point.x - imgCenter.x) * scale; 

	zoomedCenter.y += -(point.y - imgCenter.y) * scale; 

	scale *= newScale; 
}

std::complex<double> Zoom::getZoomedComplexCoord(int x, int y)
{

	double cReal = (x - imgCenter.x) * scale + zoomedCenter.x;
	double cImag = (y - imgCenter.y) * scale + zoomedCenter.y;

	std::complex<double> c (cReal, cImag);

	return c;
}

void Zoom::setImageCenter()
{
	imgCenter.x = imgWidth / 2.0;
	imgCenter.y = imgHeight / 2.0;
}