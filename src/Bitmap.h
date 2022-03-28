#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <cstdint>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

#define BYTES_PER_PIXEL 3


class Bitmap {
public:
	struct BitmapIterator; 

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~ CONSTRUCTOR(S), DESTRUCTOR ~~~~~~~~~~~~~~~~~~~~~*/

	Bitmap(const int width, const int height);
	virtual ~Bitmap();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PUBLIC METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	bool write(const std::string& outputFile);
	BitmapIterator begin() const;
    BitmapIterator end() const;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STRUCT(S) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
   struct BitmapIterator
   {
      // iterator tags
      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = uint8_t;
      using pointer = uint8_t*;
      using reference = uint8_t&;
      
      BitmapIterator(pointer ptr) : color(ptr) {};
      
      reference operator*() const { return *color; };
      pointer operator->() { return color; };
      
      BitmapIterator& operator++()
      {
         color++;
         return *this;
      };
      
      BitmapIterator operator++(int)
      {
         BitmapIterator tmp = *this;
         ++(*this);
         return tmp;
      };
      
      friend bool operator==( const BitmapIterator& bitmapItr1,
                             const BitmapIterator& bitmapItr2 )
      {
         return bitmapItr1.color == bitmapItr2.color;
      };
      
      friend bool operator!=( const BitmapIterator& bitmapItr1,
                             const BitmapIterator& bitmapItr2 )
      {
         return bitmapItr1.color != bitmapItr2.color;
      };
      
   private:
      pointer color;
   };

	
private:
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PRIVATE DATA MEMBERS ~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	// bitmap dimensions
	int width{0}; 
	int height{0}; 
	int imageSize{0}; 

	// pointer to memory storing bitmap pixels	
	uint8_t* pixelMap{nullptr};

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PRIVATE METHODS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	void setFileAndInfoHeaders(); 
	
};

#endif // BITMAP_H