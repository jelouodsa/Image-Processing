#include "src/imageprocessing.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv){
	ImageProcessing m;

	if(argc < 1){
		//cout<<"Correct format of entering is ./main [filename.pgm or filename.ppm]";
		return 0;
	}

	m.readImage(argv, 1);
	m.calculateHistogram(argv, 2);
	return 0;
}