/*
Feature Extraction FELib LICENSE

This software is freely available for non-commercial use such as research and education. 
Please see the full disclaimer below. 

We recommand you cite the reference given below in your publications related to this work.. 

Jianke Zhu, Steven C.H. Hoi, Michael R. Lyu and Shuicheng Yan, ¡°Near-Duplicate Keyframe 
Retrieval by Nonrigid Image Matching,¡± ACM Multimedia'2008.

	
Copyright (c) 2003-2008 Jianke Zhu.  Email:jkzhu@cse.cuhk.edu.hk

http://www.cse.cuhk.edu.hk/~jkzhu


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


$Revision: 1.1 $ 
$Date: 2008/08/20 $ 
*/
#ifndef __EXTRACTFEATURE_UTIL__ 
#define __EXTRACTFEATURE_UTIL__  
//#define __SSE2__ 1
//Distance metric

#ifdef __cplusplus
extern "C" {
#endif

	/* calculate the chi2-distance between two vectors/histograms of unknown alignment/size*/
FELIB_API double chi2_double(const int dim, const double* const x, const double* const y);

/* calculate the chi2-distance matrix between a set of vectors/histograms. */
FELIB_API double chi2sym_distance_double(const int dim, const int nx, const double* const x, 
                               double* const K);

/* calculate the chi2-distance matrix between two sets of vectors/histograms. */
FELIB_API double chi2_distance_double(const int dim, const int nx, const double* const x, 
                          const int ny, const double* const y, double* const K);

//Jackie's version
FELIB_API double calcuChiDist(double* va, double* vb, int n);
FELIB_API double calcuChiDistFast(double* va, double Na, double* vb, double Nb, int n);
FELIB_API double calcuSum(double* vb, int n);
FELIB_API double calcuAbsDist(double* va, double* vb, int n);
FELIB_API double calcuNorm(double* va, double* vb, int n);



//mean, vector normalization
FELIB_API double MeanVector(double* v, int vSize);
FELIB_API void ZeroMeanUnitLength( double* v, int vSize);
FELIB_API double vmax(double* data, int DataSize);
FELIB_API double vmin(double* data, int DataSize);
FELIB_API int ivmax(int* data, int DataSize);

//histogram
FELIB_API double NormalizeHisto(double* vb, int n);

//lost image set
FELIB_API ImgFileList* LoadImgList(char* flder);
FELIB_API void RemoveFileNameExt(char* filename);
FELIB_API void LoadFeatureBank( char* flder, FeaBanks* feaBanks );
FELIB_API void freeImgFileList(ImgFileList* imgList);

//debug the cvmat format image
FELIB_API int save_mat_image(CvMat* mat, char* name);

//load, save data in binary format, compact than plain text
FELIB_API CvMat*  GetMat2( FILE *fh, BOOL isVector );
FELIB_API CvMat*  GetMat( FILE *fh, BOOL isVector );
FELIB_API int WriteMat(CvMat* m, FILE *fh, BOOL isVector );
FELIB_API int WriteMat2(CvMat* m, FILE *fh, BOOL isVector ) ;
FELIB_API int writeData(double* v, int m, int n, FILE* fh);
FELIB_API double* getData(FILE* fh, int* m, int *n);

//image format conversion
FELIB_API void IplimgToArray(IplImage* im, uchar* arr);
FELIB_API double* iplToDArr(IplImage* img);
FELIB_API IplImage* resizeGImg( IplImage* img, int mask_size );

#ifdef __cplusplus
}
#endif


#endif /*__EXTRACTFEATURE_UTIL__*/