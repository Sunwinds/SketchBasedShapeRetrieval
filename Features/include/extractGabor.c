/*
Feature Extraction FELib LICENSE

This software is freely available for non-commercial use such as research and education. 
Please see the full disclaimer below. 

We recommand you cite the reference given below in your publications related to this work.. 

Jianke Zhu, Steven C.H. Hoi and Michael R. Lyu,
"Face Annotation by Transductive Kernel Fisher Discriminant,"
IEEE Trans. on Multimedia, vol. 10, Jan. 2008, pp. 86-96. 
	
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

#include "felib.h"
/**
  @author   Zhu Jianke
  @version  8-18-2008

  @memo     Extract Gabor wavelets transform features
  @doc      Extract Gabor wavelets transform features of a given image list
  
  @param    imgList		    image list
 
  @param	gaborOpt		gaborOpt[0]--size of Gabor filter mask, default 64; 
							gaborOpt[1]--number of scale of Gabor filter, default 5;
							gaborOpt[2]--number of orientation of Gabor filter, default 8;  
							gaborOpt[3]--control the sample rate for global representation, unused for Gabor moment, default 8;
 
  @param	flen			return the length for each extracted image feature

  @return   void
*/
double* extractFeatures( ImgFileList* imgList, int gaborOpt[4], int* flen)
{
	// various image formats
	IplImage* img;
	IplImage* gimg;

	//Gabor related parameters
	int		mask_size = gaborOpt[0]; //64
	int		scale	  = gaborOpt[1]; //5
	int		ori		  = gaborOpt[2]; //8
	int		skip	  = gaborOpt[3]; //8
	CvMat** mGabor;

 	int  i, j, gaborDim;//FEATURE_LEN;

	//feature vector
	double *gvec; 
	double *featureBank;

	if( imgList->nbImg<=0 )	return 0;

	gaborDim = scale*ori*mask_size*mask_size/(skip*skip);

	//feature vector length
	*flen = gaborDim;
	gvec  = Malloc( double, gaborDim );

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

		//convert to grayscale, prepare the data for LBP histogram
		gimg  = cvCreateImage( cvGetSize(img), 8, 1 );
		if(img->nChannels==3)
			cvCvtColor(img, gimg, CV_BGR2GRAY);
		else
			cvCopy( img, gimg, 0);
		
		//Gabor wavelet transform
		extractGabor( gimg, gvec,mask_size, scale, ori, skip, mGabor);

		cvReleaseImage( &gimg );
		cvReleaseImage( &img );
		
		// save into a buffer
		for(j=0; j<gaborDim; j++) featureBank[(*flen)*i + j] = gvec[j];
	}

	UnloadGaborFFT( mGabor, scale, ori );

 	free(gvec);	

	return featureBank;
}


int main(int argc, char **argv)
{
	int	flen, gaborOpt[4];
	FILE* fp;
	ImgFileList* imList; 
	double  *data;
	if(argc<2) return(0);
	
	// Load imgList
	imList = LoadImgList( argv[1] );
		
	gaborOpt[0] = 128;	gaborOpt[1] = 5;	
	gaborOpt[2] = 8;	gaborOpt[3] = 8;

	data = extractFeatures( imList, gaborOpt, &flen );

	fp = fopen("data.bin" ,"wb");
	writeData( data, imList->nbImg, flen,  fp );
	fclose(fp);
 
	free(data);
	freeImgFileList( imList );
	return (0);
}
