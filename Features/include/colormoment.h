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
#ifndef __EXTRACTFEATURE_COLORMOMENT__ 
#define __EXTRACTFEATURE_COLORMOMENT__   
FELIB_API void extractHistogram(IplImage* src, double* histoVec, int h_bins, int s_bins );
FELIB_API void extractHistogram3D(IplImage* src, double* histoVec, int h_bins, int s_bins, int v_bins );
FELIB_API void calcuMoment(IplImage* img, double* mome);
FELIB_API void calcuVectorMoment(double* vec, int n, double scale, double* mome);
FELIB_API void calcuBlockMoment(IplImage* img, double* mome, int n1, int n2, int colorSpace);
#endif /*__EXTRACTFEATURE_COLORMOMENT__*/