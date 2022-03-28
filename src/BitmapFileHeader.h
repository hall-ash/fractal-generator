#ifndef BITMAPFILEHEADER_H
#define BITMAPFILEHEADER_H
#include <cstdint>

#pragma pack(push, 2)

struct BitmapFileHeader 
{
	char header[2]{'B', 'M'}; // indicates file is bitmap
	int32_t fileSize; // final size of file
	int32_t reserved{0};
	int32_t dataOffset; // when the data actually begins
};

#pragma pack(pop)

#endif // BITMAPFILEHEADER_H