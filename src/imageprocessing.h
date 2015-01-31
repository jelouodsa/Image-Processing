#ifndef _IMAGEPROCESSING_H_
#define _IMAGEPROCESSING_H_

class ImageProcessing{
public:
	//variables ... image headers
	int numberOfColumns, numberOfRows, numberOfBands, highVal, totalPixels, header, highHisto;
	unsigned char * image, * histogram, * outimageHistogram;
	//functions
	void readImage(char **argv, int k);
	void writeImage(char **argv, int k);
	void calculateHistogram(char **argv, int k);	

};

#endif