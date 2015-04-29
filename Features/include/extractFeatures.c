#include "extractFeatures.h"

#pragma  once
#pragma  message("felib.h --> Linking with felib.lib")
#pragma comment(lib, "felib.lib")

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
double* extractFeatures( imgFile* imgfile, int gaborOpt[4], int gistOpt[4], double* wght, int* flen)
{
	// various image formats
	IplImage* srcImg;
	IplImage* img;
	IplImage* gimg;

	uchar*	  uimg;
	uchar*	  guimg;
	int*	  giimg;

	//Gabor related parameters
	int		mask_size = gaborOpt[0]; //64
	int		scale	  = gaborOpt[1]; //5
	int		ori		  = gaborOpt[2]; //8
	int		skip	  = gaborOpt[3]; //8
	CvMat** mGabor;
	//Gist parameters
	int gist_ori[4];
	int gist_scale = gistOpt[0]; //4;
	int gist_size  = gistOpt[1]; //128;
	int gist_nb    = gistOpt[2]; //4;
	int gist_fc    = gistOpt[3]; //4;
	int nbf;
	double* mG;
	double* im;
	IplImage* gistim = cvCreateImage(cvSize( gist_size, gist_size ), 8, 3);
	IplImage* gistimSingle = cvCreateImage(cvSize( gist_size, gist_size ), 8, 1);

	int j, k, edgeDim, gaborDim, lbpDim, gistDim;//FEATURE_LEN;

	//feature vector
	double *cvec, *lvec, *gvec, *evec, *ivec; 
	double *featureBank;

	gist_ori[0] = gist_ori[1] = gist_ori[2] = gist_ori[3] = 8;
	// Create gabor filer bank to extract GIST feature
	mG = getGISTFilter( gist_size, gist_scale, gist_ori, &nbf );

	lbpDim   = 59;// modify it from the returned value
	edgeDim  = 36+1;
	gaborDim = scale*ori*3;
	gistDim  = nbf*gist_nb*gist_nb;

	//feature vector length
	//flen = Malloc( int, 1);
	*flen = lbpDim + gaborDim + edgeDim + gistDim;

	lvec = Malloc( double, lbpDim );
	evec = Malloc( double, edgeDim );
	gvec = Malloc( double, gaborDim );
	ivec = Malloc( double, gistDim );

	// Return feature bank
	featureBank = Malloc( double, *flen);
	memset( featureBank, 0, *flen * sizeof(double) );

	// generate gabor filter 
	mGabor = getGaborFFT( mask_size, scale, ori );

	srcImg = cvLoadImage(imgfile->fname,-1);	
	if(!srcImg)
	{
		printf( "Failed to load image: %s\n" , imgfile->fname );

	}

	img = cvCreateImage(cvSize( 500, 400 ), srcImg->depth, srcImg->nChannels);
	cvResize(srcImg, img, 1);
    cvReleaseImage(&srcImg);
	//1. Local binary pattern histogram, 59 dim with mapping
	guimg = Malloc( uchar, img->width*img->height );
	giimg = Malloc( int, img->width*img->height );

	//convert to grayscale, prepare the data for LBP histogram
	gimg  = cvCreateImage( cvGetSize(img), 8, 1 );
	if(img->nChannels==3)
		cvCvtColor(img, gimg, CV_BGR2GRAY);
	else
		cvCopy( img, gimg, 0);

	IplimgToArray( gimg, guimg );
	for(j=0; j<img->width; j++) 
		for(k=0; k<img->height; k++) 
			giimg[j*img->height+k] = (int)guimg[k*img->width+j];

	lbp( giimg, img->width, img->height, 1., 8, lvec, &lbpDim );

	//clean up
	free(guimg);
	free(giimg);

	//2. Gabor wavelet feature moment
	//extractGabor( gimg, gvec,mask_size, scale, ori, skip, mGabor);
	extractGaborMoment( gimg, gvec, mask_size, scale, ori, mGabor);	

	//3. GIST feature
	if(img->nChannels==3)
	{
		cvResize( img, gistim, CV_INTER_LINEAR );
		im = iplToDArr(gistim);
	}else
	{
		cvResize( img, gistimSingle, CV_INTER_LINEAR );
		im = iplToDArr(gistimSingle);
	}

	// preprocess image
	prefilt( im, gistim->width, gistim->height, gist_fc );
	// extract gist feature
	ivec = gist( mG, nbf, gist_size, im, gist_nb );

	im = NULL;
	//free(im);
	cvReleaseImage( &gimg );

	//4. Edge histogram
	uimg  = Malloc( uchar, img->width*img->height*img->nChannels);
	IplimgToArray( img, uimg );
	Edge_Direction_Histogram(uimg, img->width, img->height, THR_EDGE, BIN_NUM, evec);		


	//clean up
	free(uimg);
	cvReleaseImage( &img );

	// save into a buffer
	k  = 0;

	for(j=0; j<edgeDim; j++)  featureBank[k + j] = wght[0]*evec[j];
	k += edgeDim;
	for(j=0; j<gaborDim; j++) featureBank[k + j] = wght[1]*gvec[j];
	k += gaborDim; 
	for(j=0; j<lbpDim; j++)   featureBank[k + j] = wght[2]*lvec[j];	
	k += lbpDim;
	for(j=0; j<gistDim; j++)  featureBank[k + j] = wght[3]*ivec[j];		

	mG = NULL;
	//free( mG );
	cvReleaseImage( &gistim );
	cvReleaseImage( &gistimSingle );

	UnloadGaborFFT( mGabor, scale, ori );

	//free(lvec);	
	//free(gvec);	
	//free(evec);
	//free(ivec);

	lvec = NULL;
	gvec = NULL;
	evec = NULL;
	ivec = NULL;

	return featureBank;
} 