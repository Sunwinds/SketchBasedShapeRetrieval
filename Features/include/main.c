/*
Feature Extraction FELib LICENSE

This software is freely available for non-commercial use such as research and education. 
Please see the full disclaimer below. 

We recommand you cite the reference given below in your publications related to this work.. 

Jianke Zhu, Steven C.H. Hoi, Michael R. Lyu and Shuicheng Yan, ¡°Near-Duplicate Keyframe 
Retrieval by Nonrigid Image Matching,¡± ACM Multimedia'2008.

	
Copyright (c) 2003-2009 Jianke Zhu.  Email:jianke.zhu at gmail.com
http://www.vision.ee.ethz.ch/~zhuji



3RD PART SOFTWARE

The software is partly based on the following libraries:

  - The Intel(tm) OpenCV Library
 
DISCLAIMER

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the
use of this software.

Permission is granted to anyone to use this software for any non-commercial 
purpose, and to alter it, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
   that you wrote the original software. 

2. Altered source versions must be plainly marked as such, and must not be 
   misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

--

No guarantees of performance accompany this software, nor is any 
responsibility assumed on the part of the author.

This software is provided by Jianke Zhu ``as is'' and any express or implied
warranties, including, but not limited to, the implied warranties of merchan-
tability and fitness for a particular purpose are disclaimed. In no event shall  
Jianke Zhu be liable for any direct, indirect, incidental, special, exemplary,
or consequential damages (including, but not limited to, procurement of substitute
goods or services; loss of use, data, or profits; or business interruption) however 
caused and on any theory of liability, whether in contract, strict liability, 
or tort (including negligence or otherwise) arising in any way out of the use 
of this software, even if advised of the possibility of such damage.


$Revision: 1.2 $ 
$Date: 2008/12/31 $ 
*/
//comment this line for command line, with this Macro, it will complile and link as a matlab MEX API

#define MATLAB_API

#ifdef MATLAB_API
#include "mex.h"
#endif


#include "felib.h"
/**
  @author   Zhu Jianke
  @version  8-18-2008

  @memo     Extract image features
  @doc      Extract image features of a given image list
  
  @param    imgList		    image list
  @param    colorOpt		color feature options: 
						        1. HSV color histogram; 
								2. HSV 3D color histogram 
								3. RGB color moment 
								4. Lab color moment
								5. RGB pyramid color moent
  @param	binOpt			for color histogram: hb = binOpt[0]; sb = binOpt[1];	vb = binOpt[2]; 
							for color moment:  binOpt[0] -- number of x grid;  binOpt[1] -- number of y grid; 
							binOpt[2] -- undefined, any;  
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

  @return   void
*/
double* extractFeatures( ImgFileList* imgList, int colorOpt, int binOpt[3], int gaborOpt[4], int gistOpt[4], double* wght, int* flen)
{
	// various image formats
	IplImage* img;
	IplImage* gimg;
	
	uchar*	  uimg;
	uchar*	  guimg;
	int*	  giimg;
	// color feature option
	int hb, sb, vb;
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

 	int  i, j, k, colorDim, edgeDim, gaborDim, lbpDim, gistDim;//FEATURE_LEN;

	//feature vector
	double *cvec, *lvec, *gvec, *evec, *ivec; 
	double *featureBank;

	if( imgList->nbImg<=0 )	return 0;

	hb = binOpt[0]; sb = binOpt[1];	vb = binOpt[2]; 

	gist_ori[0] = gist_ori[1] = gist_ori[2] = gist_ori[3] = 8;
	// Create gabor filer bank to extract GIST feature
	mG = getGISTFilter( gist_size, gist_scale, gist_ori, &nbf );

	//Calculate the dimensionality of the feature vector
	if(colorOpt==1||colorOpt==2) 
		colorDim = hb*sb*vb;
	else if(colorOpt==3 || colorOpt==4)
		colorDim = hb*sb*9;
	else if(colorOpt==5)
	{
		k = 0;
		for(i=0; i<=hb; i++) k += (int)pow( 4, i );
		colorDim = k*9;
	}

	lbpDim   = 59;// modify it from the returned value
	edgeDim  = 36+1;
	gaborDim = scale*ori*3;
#ifdef GIST_MOMENT
	gistDim  = nbf*gist_nb*gist_nb*3;
#else
	gistDim  = nbf*gist_nb*gist_nb;
#endif
	//feature vector length
	*flen = colorDim + lbpDim + gaborDim +edgeDim+gistDim;

	cvec = Malloc( double, colorDim );
	lvec = Malloc( double, lbpDim );
	evec = Malloc( double, edgeDim );
	gvec = Malloc( double, gaborDim );
	ivec = Malloc( double, gistDim );

	// Return feature bank
	featureBank = Malloc( double, *flen * imgList->nbImg );
	memset( featureBank, 0, *flen * imgList->nbImg*sizeof(double) );

	// generate gabor filter 
	mGabor = getGaborFFT( mask_size, scale, ori );

	for(i=0;i<imgList->nbImg;i++)
	{
		img   = cvLoadImage(imgList->imfile[i].fname,-1);	
		if(!img)
		{
			printf( "Failed to load image: %s\n" , imgList->imfile[i].fname );
			continue;
		}else
		{
			printf( "." );//printf( "%d %s\n",i+1,imgList->imfile[i].fname);
			if( i%10==9 ) printf("\n");
		}

		//1. Color moment, we suppose that all input images are color, the grayscale single channel image
		// will be converted into three channel image
		if( colorOpt==1 ) 
			extractHistogram(img, cvec, hb, sb );		//HSV color histogram
		else if( colorOpt==2 )
			extractHistogram3D(img, cvec, hb, sb, vb ); //HSV 3D color histogram
		else if( colorOpt==3 ) 
			calcuBlockMoment(img, cvec, hb, sb, 1 );	//RGB color space
		else if( colorOpt==4 ) 
			calcuBlockMoment(img, cvec, hb, sb, 3 );	//Lab color space
		else if( colorOpt==5 )
		{
			k = 0;
			for(j=0; j<=hb; j++) 
			{	
				calcuBlockMoment( img, cvec + k, (int)pow( 2, j), (int)pow( 2, j ), 1 );
				k += (int)pow( 4, j )*9;
			}
		}

		//2. Local binary pattern histogram, 59 dim with mapping
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

		//3. Gabor wavelet feature moment
		//extractGabor( gimg, gvec,mask_size, scale, ori, skip, mGabor);
		extractGaborMoment( gimg, gvec, mask_size, scale, ori, mGabor);	

		// 4. GIST feature
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

		free(im);
		cvReleaseImage( &gimg );
 
		//5. Edge histogram
		uimg  = Malloc( uchar, img->width*img->height*img->nChannels);
		IplimgToArray( img, uimg );
		Edge_Direction_Histogram(uimg, img->width, img->height, THR_EDGE, BIN_NUM, evec);		


		//clean up
		free(uimg);
		cvReleaseImage( &img );
		
		// save into a buffer
		k  = 0;
		for(j=0; j<colorDim; j++) featureBank[(*flen)*i + k + j] = wght[0]*cvec[j];
		k += colorDim;
		for(j=0; j<edgeDim; j++)  featureBank[(*flen)*i + k + j] = wght[1]*evec[j];
		k += edgeDim;
		for(j=0; j<gaborDim; j++) featureBank[(*flen)*i + k + j] = wght[2]*gvec[j];
		k += gaborDim; 
		for(j=0; j<lbpDim; j++)   featureBank[(*flen)*i + k + j] = wght[3]*lvec[j];	
		k += lbpDim;
		for(j=0; j<gistDim; j++)  featureBank[(*flen)*i + k + j] = wght[4]*ivec[j];		

	}
	
	free( mG );
	cvReleaseImage( &gistim );
	cvReleaseImage( &gistimSingle );

	UnloadGaborFFT( mGabor, scale, ori );

 	free(cvec);	
 	free(lvec);	
 	free(gvec);	
	free(evec);
	free(ivec);

	return featureBank;
}

#ifndef MATLAB_API
int main(int argc, char **argv)
{
	int	flen, binOpt[3], gaborOpt[4], gistOpt[4], colorOpt;
	FILE* fp;
	ImgFileList* imList; 
	double	awght[5], *wght, *data;
	if(argc<2) return(0);
		// Load imgList
	imList = LoadImgList( argv[1] );
		
	colorOpt  = 3; 
	binOpt[0] = 3; binOpt[1] = 3; binOpt[2] = 1;
	
	gaborOpt[0] = 64;	gaborOpt[1] = 5;	
	gaborOpt[2] = 8;	gaborOpt[3] = 8;

	awght[0] = awght[1] = awght[2] = 1.0;	
	awght[3] = 20.0; awght[4] = 7.0;
	wght = awght;

	gistOpt[0] = 4;
	gistOpt[1] = 256;
	gistOpt[2] = 4;
	gistOpt[3] = 4;

	data = extractFeatures( imList, colorOpt, binOpt, gaborOpt, gistOpt, wght, &flen );

	fp = fopen("data.bin" ,"wb");
	writeData( data, imList->nbImg, flen,  fp );
	fclose(fp);
 
	free(data);
	freeImgFileList( imList );
	return (0);
}
#endif 


#ifdef MATLAB_API
/**
  @author   Zhu Jianke
  @version  8-18-2008

  @memo     Matlab interface for image feature extraction
  @doc      Matlab interface for image feature extraction
  
  @param    prhs[0]		    root path for these images, thus only need store the relative path
  @param    prhs[1]			image file name list
  @param    prhs[2]			assign an image id for each image in the list, will use it for matching purpose
  @param    prhs[3]			paramters for color feature extraction
							param[0]--color feature options: 1.HSV color histogram; 2.HSV 3D color histogram 
								3.RGB Color moment 4.Lab color moment
							param[1-3]--for color histogram: number of bins for 2D/3D histogram, note as hb, sb, vb; 
									  --for color moment: number of x/y grid, param[3] is undefined in this case;  
							param[4]--size of Gabor filter mask, default 64; 
							param[5]--number of scale of Gabor filter, default 5;
							param[6]--number of orientation of Gabor filter, default 8;  
							param[7]--control the sample rate for global representation, unused for Gabor moment, default 8;
							param[8-11] GIST option
							param[8]-  number of GIST scale 4
							param[9]- filter mask size is 256
							param[10]- number of block to extract moment 4
							param[11]- fc for preprocessing, filter the image

  @param    prhs[4]			the weight to balance the contribution for each component, color, edge, Gabor, and LBP
							the coefficient is manually assigned, roughly 1, 1, 1, 20 7. The optimization of these coefficients is 
							knowns ensemble learning
  @param    plhs[0]			feature matrix with size of (total number images) x (feature length) 

  @return   void
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])                
{	
	//Load dataset
	char    buf[MAXLENGTH];
	double	*idx, *param, awght[5], *wght, *ptr, *data;
	int		i, nbImg, flen, binOpt[3], gaborOpt[4], gistOpt[4], colorOpt;
	ImgFileList* imList; 
	mxArray *tmp;
	
	if(nrhs<1)
	{
		printf( "Too few input!\n" );
	}else
	{
		imList	     = Malloc(ImgFileList, 1 );
		imList->path = Malloc( char, MAXLENGTH );
		imList->path = mxArrayToString(prhs[0]);
		nbImg   = (int)mxGetN(prhs[1]);
		idx		= mxGetPr(prhs[2]);
		param	= mxGetPr(prhs[3]);
		wght	= mxGetPr(prhs[4]);
		if( nrhs <= 3 )
		{
			colorOpt  = 3; 
			binOpt[0] = 3; binOpt[1] = 3; binOpt[2] = 1;
			gaborOpt[0] = 64;	gaborOpt[1] = 5;	
			gaborOpt[2] = 8;	gaborOpt[3] = 8;
			awght[0] = awght[1] = awght[2] = 1.0;	
			awght[3] = 20.0;  awght[4] = 7.0;
			wght = awght;
			gistOpt[0] = 4;
			gistOpt[1] = 256;
			gistOpt[2] = 4;
			gistOpt[3] = 4;

		}else{
			colorOpt    = (int)param[0];
			binOpt[0]   = (int)param[1];
			binOpt[1]   = (int)param[2];	
			binOpt[2]   = (int)param[3];
			gaborOpt[0] = (int)param[4];	
			gaborOpt[1] = (int)param[5];	
			gaborOpt[2] = (int)param[6];	
			gaborOpt[3] = (int)param[7];
			gistOpt[0]  = (int)param[8];	
			gistOpt[1]  = (int)param[9];	
			gistOpt[2]  = (int)param[10];	
			gistOpt[3]  = (int)param[11];
		}

		imList->nbImg	= nbImg;
		imList->imfile = Malloc( imgFile, nbImg );
		
		for (i=0; i<nbImg; i++)
		{
			tmp = mxGetCell(prhs[1], i);
			imList->imfile[i].id	 = (int)idx[i];
			imList->imfile[i].fname = Malloc( char, MAXLENGTH );
			strcpy( buf, mxArrayToString(tmp) );
			sprintf( imList->imfile[i].fname,"%s/%s", imList->path, buf );
		}
	
		// detection routines
		data = extractFeatures( imList, colorOpt, binOpt, gaborOpt, gistOpt, wght, &flen );

		// Compute cmc curve, can be done by matlab
		plhs[0] = mxCreateDoubleMatrix( flen, nbImg, mxREAL );
		ptr = mxGetPr(plhs[0]);
		memcpy( ptr, data, sizeof(double)*nbImg*flen );

		// Compute precision recall	
		free(data);
		
		freeImgFileList( imList );
	}
}
#endif