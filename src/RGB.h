#ifndef RGB_H
#define RGB_H

class RGB
{
public:
	double red;
	double green;
	double blue;

	RGB() : red(0), green(0), blue(0) {};

	RGB(double red, double green, double blue) :
		red(red), green(green), blue(blue) {};
	
	virtual ~RGB() {};

	friend RGB operator-(const RGB& first, const RGB& second)
	{
		return RGB(first.red - second.red, 
			first.green - second.green, 
			first.blue - second.blue);
	};

	// RGB& operator=(RGB& rgb)
	// {
	// 	return rgb; 
	// }

	
};

#endif // RGB_H