/** 
 * @file test.cpp
 * @brief  Test app
 * @author Vikas MK
 * @version 1.0
 * @date 2015-08-07
 */

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>

 using namespace std;
 using namespace cv;

#define NO_OF_BINS 256
 class ImageInfo
{
    Mat imageRaw;
    int histSize ;/*Size of histogram*/
    vector<Mat> bgrPlanes; /*Histogram will be split into rgb subspace*/
    float range[2];
    const float* histRange;
};

ImageInfo::ImageInfo(Mat aMat)
{
    Mat b_hist,r_hist,g_hist;
    histSize = NO_OF_BINS;
    /*Copy to imageRaw*/
   aMat.copyTo (imageRaw);
   cv::split(imageRaw,bgrPlanes);

   range[0] = 0;
   range[1] = NO_OF_BINS;

   histRange =  range ;

   calcHist(&bgrPlanes[0],1,0,Mat(),b_hist,1,&histSize,true,false);
}
#define NO_IMAGES 10

/*Open all files in a given path*/
int main()
{

    string images[NO_IMAGES+1];
    Mat img_raw;

    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        stringstream ss;
        ss << "./training_images/coco_images/coco" <<fileNumber<<".jpg"<<endl;
        string filename;
        ss >> filename;
        images[fileNumber] = filename;
        cout << images[fileNumber]<<endl;
    }

    /*Display */
    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        /*read image into mat type*/
        img_raw = cv::imread(images[fileNumber],1);

        if(img_raw.data)
        {
            namedWindow("Display Image", WINDOW_AUTOSIZE );
            cv::imshow("Display Image",img_raw);
            waitKey(0);
        }
    }

}
