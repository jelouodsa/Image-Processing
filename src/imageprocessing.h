#ifndef _IMAGEPROCESSING_H_
#define _IMAGEPROCESSING_H_

class ImageProcessing{
public:
	//variables ... image headers
	int numberOfColumns, numberOfRows, numberOfBands, highVal, totalPixels, header;
	unsigned char * image;
	//functions
	void readImage(char **argv);
	void writeImage(char **argv);

};

#endif