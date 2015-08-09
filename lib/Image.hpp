#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#ifndef IMAGE_CPP_H
#define IMAGE_CPP_H

using namespace cv;
#define NO_OF_BINS 64 
class Image
{
    private:
        float range[2];
        vector<Mat> bgrPlanes; /*Histogram will be split into rgb subspace*/
        int histSize ;/*Size of histogram*/
        const float* histRange;
    public:
        Mat imageRaw;
        Mat b_hist,r_hist,g_hist; /*histogram of all 3 channels*/
        string FileName;
        Image(void);
        Image(Mat aMat); /*Initializes the image info, and calculates histogram*/
        void DisplayHistogram(void);
        
        Mat rawHistData;/*Contains raw rgb histogram data*/
};
#endif
