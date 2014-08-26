#ifndef _IMAGEPROCESSING_H_
#define _IMAGEPROCESSING_H_

void print();

class ImageProcessing{
public:
	//variables ... image headers
	int numberOfColumns, numberOfRows, numberOfBands, highVal, totalPixels;
	unsigned char * image;
	//functions
	void readImage(char **argv);

};

#endif