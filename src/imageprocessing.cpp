#include "imageprocessing.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#define FALSE 0;
#define TRUE 1;

using namespace std;


void ImageProcessing::readImage(char **argv, int k){
	FILE * fpIn;
	char * string;
	int doneReading = FALSE;
	char c;

	fpIn = fopen(argv[k], "rb");
	if(fpIn == NULL){
		cerr<<"Such a file does not exist...";
		exit;
	}
	string = (char *) calloc(256,1);
	while(!doneReading && (c = (char) fgetc(fpIn)) != '\0')
		switch(c){
			case 'P':
				c = (char) fgetc(fpIn);
				switch(c){
					case '2':
						this->header = 2;
						this->numberOfBands = 1;
						//pgm plain
					break;
					case '5':
						this->header = 5;
						this->numberOfBands = 1;
						//pgm Normal
					break;
					case '3':
						this->header = 3;
						this->numberOfBands = 3;
						//ppm plain
					break;
					case '6':
						this->header = 6;
						this->numberOfBands = 3;
						//ppm Normal
					break;
				}
				c = (char) fgetc(fpIn);
				if(c != 0x0A){
					ungetc(c, fpIn);
				}
				else{
					ungetc(c, fpIn);
					fgets(string, 256, fpIn);
				}
			break;
			case '#':
			fgets(string, 256, fpIn);
			cout<<"File you entered is "<<string<<"\n";
			break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ungetc(c, fpIn);
				fscanf(fpIn,"%d %d %d", &(this->numberOfColumns), &(this->numberOfRows), &(this->highVal));
				doneReading = TRUE;
				fgetc(fpIn);
			break;
		}
	this->totalPixels = this->numberOfRows*this->numberOfColumns*this->numberOfBands;
	this->image = (unsigned char *) malloc (this->totalPixels);
	fread(this->image,1,this->totalPixels,fpIn);
	cout<<"Reading the image "<<argv[k]<<" was sucessfull...\n";
}

void ImageProcessing::writeImage(char **argv, int k){
	FILE * fpOut;

	fpOut = fopen(argv[k], "wb");
	if(fpOut == NULL){
		cerr<<"Error couldn't write the image "<<argv[k]<<"...\n";
		exit;
	}
	fprintf(fpOut, "P%d\n%d %d\n%d\n",this->header,this->numberOfColumns, this->numberOfRows, this->highVal );
	fwrite(this->image,1,this->totalPixels,fpOut);
	cout<<"Wrote the image into "<<argv[k]<<"...\n";
}

void ImageProcessing::calculateHistogram(char **argv, int k){
	bool flagbands = FALSE;
	int i, j;
	int hr, hg, hb, hgr, hrgb;

	ImageProcessing m;

	this->histogram = (unsigned char *) malloc (this->highVal*this->numberOfBands);

	if (this->numberOfBands == 3)
	{
		flagbands = TRUE;
	}
	if (flagbands)
	{
		hr = this->image[0];
		hg = this->image[1];
		hb = this->image[2];
		for (i = 0; i < this->totalPixels/this->numberOfBands; i++)
		{
			for (j = 0; j < this->numberOfBands; j++)
			{
				this->histogram[this->image[i*this->numberOfBands + j]] += 1;
			}
		}
	}
	else
	{
		hgr = this->image[0];
		for (i = 0; i < this->totalPixels; i++)
		{
			this->histogram[this->image[i]] += 1;
		}
	}
	if (flagbands)
	{
		for (i = 0; i < this->highVal; i++)
		{
			if (this->histogram[i*numberOfBands] > hr)
			{
				hr = this->histogram[i*numberOfBands];
			}
			if (this->histogram[i*numberOfBands +1] > hg)
			{
				hg = this->histogram[i*numberOfBands +1];
			}
			if (this->histogram[i*numberOfBands +2] > hb)
			{
				hb = this->histogram[i*numberOfBands +2];
			}
		}
		hrgb = hr;
		if (hrgb < hg)
		{
			if (hg < hb)
			{
				hrgb = hb;
			}
			else
			{
				hrgb = hg;
			}
		}
		if (hrgb < hg)
		{
			if (hr < hb)
			{
				hrgb = hb;
			}
		}
		this->outimageHistogram = (unsigned char *) malloc ((hrgb+10)*this->highVal*this->numberOfBands);
		m.totalPixels = (hrgb+10)*this->highVal*this->numberOfBands;
		m.numberOfRows = hrgb;
	}
	else
	{
		for (i = 0; i < this->highVal; i++)
		{
			if (this->histogram[i] >hgr)
			{
				hgr = this->histogram[i];
			}
		}
		this->outimageHistogram = (unsigned char *) malloc ((hrgb+10)*this->highVal*this->numberOfBands);
		m.totalPixels = (hgr+10)*this->highVal*this->numberOfBands;
		m.numberOfRows = hgr;
	}
	if (flagbands)
	{
		this->highHisto = hrgb;
	}
	else
	{
		this->highHisto = hgr;
	}
	m.image = this->outimageHistogram;
	m.numberOfBands = this->numberOfBands;
	m.numberOfColumns = this->highVal;
	m.highVal = 255;
	m.header = this->header;
	for (j = 0; j < this->highVal; j++)
	{
		for (i = 0; i < this->highVal; i++)
		{
			for (int k = 0; k < this->numberOfBands; k++)
			{
				if (this->highHisto - i < this->histogram[j+k])
				{
					this->outimageHistogram[j+k+ i*this->highVal*this->numberOfBands] = 255;
				}
				else
				{
					this->outimageHistogram[j+k+ i*this->highVal*this->numberOfBands] = 0;
				}
			}
		}
	}
	m.writeImage(argv, k);
}