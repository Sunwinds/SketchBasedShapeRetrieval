#ifndef EXTRACTFEATURE_H 
#define EXTRACTFEATURE_H

#include "felib.h"

	/**

	@memo     Extract image features
	@doc      Extract image features of a given image list

	@param    imgfile		    image file

	@param	gaborOpt		gaborOpt[0]--size of Gabor filter mask, default 64; 
	gaborOpt[1]--number of scale of Gabor filter, default 5;
	gaborOpt[2]--number of orientation of Gabor filter, default 8;  
	gaborOpt[3]--control the sample rate for global representation, unused for Gabor moment, default 8;
	@param	gistOpt			gistOpt[0]-- scale 4
	gistOpt[1]-- size  128
	gistOpt[2]-- number of block to extract moment
	gistOpt[3]-- fc for preprocessing, filter the image
	@param	wght			the weight to balance the contribution for each component, color, edge, Gabor, and LBP
	the coefficient is manually assigned, roughly 1, 1, 1, 20. The optimization of these coefficients is 
	knowns ensemble learning
	@param	flen			return the length for each extracted image feature

	@return   double
	*/
	double* extractFeatures( imgFile* imgfile, int gaborOpt[4], int gistOpt[4], double* wght, int* flen);


#endif