#include <fstream>
#include <iostream>
#include "Bitmap.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ CONSTRUCTOR(S), DESTRUCTOR ~~~~~~~~~~~~~~~~~~~~~*/

Bitmap::Bitmap(const int width, const int height) : 
	width(width), height(height)
{
	imageSize = BYTES_PER_PIXEL * width * height;
	pixelMap = new uint8_t[imageSize];

	setFileAndInfoHeaders();
}

Bitmap::~Bitmap()
{
	delete[] pixelMap; 
	pixelMap = nullptr; 
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

bool Bitmap::write(const std::string& outputFile)
{
	std::ofstream file;
	file.open(outputFile, std::ios::out | std::ios::binary);

	if (!file) 
	{ 
		std::cerr << "Error accessing file" << std::endl;
		return false; 
	}


	file.write( reinterpret_cast<const char *>( &fileHeader ),
              sizeof(BitmapFileHeader) );
    file.write( reinterpret_cast<const char *>( &infoHeader ),
              sizeof(BitmapInfoHeader) );
    file.write( reinterpret_cast<const char *>( pixelMap ),
              imageSize );

	file.close();

	return true;
}

Bitmap::BitmapIterator Bitmap::begin() const
{
   return BitmapIterator(pixelMap);
}

Bitmap::BitmapIterator Bitmap::end() const
{
   return BitmapIterator(&pixelMap[imageSize]);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Bitmap::setFileAndInfoHeaders()
{
	// bitmap file info 
	fileHeader.fileSize = sizeof(BitmapFileHeader) 
		+ sizeof(BitmapInfoHeader) + sizeof(imageSize);
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

	// bitmap image info
	infoHeader.width = width;
	infoHeader.height = height;
}




