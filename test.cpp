/**
 * @file test.cpp
 * @brief  Test app
 * @author Vikas MK
 * @version 1.1
 * @date 2015-08-07
 */

/*Revision history*/
/*1.0 : Created */
/*1.1 : Added Image class and methods. Compiles, doesnt' work */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace std;
using namespace cv;
#define NO_OF_BINS 256
class Image
{
public:
    Mat imageRaw;

    string FileName;
    Mat b_hist,r_hist,g_hist; /*histogram of all 3 channels*/
    int histSize ;/*Size of histogram*/
    vector<Mat> bgrPlanes; /*Histogram will be split into rgb subspace*/
    float range[2];
    const float* histRange;

    Image(void);
    Image(Mat aMat); /*Initializes the image info, and calculates histogram*/
    void DisplayHistogram(void);
};


Image::Image(Mat aMat)
{
    histSize = NO_OF_BINS;
    /*Copy to imageRaw*/
    aMat.copyTo (imageRaw);
    cv::split(imageRaw,bgrPlanes);

    range[0] = 0;
    range[1] = NO_OF_BINS;

    histRange =  range ;
    cv::calcHist(&bgrPlanes[0],1,0,Mat(),b_hist,1,&histSize,&histRange,true,false);
}

void Image::DisplayHistogram(void)
{
    int hist_w = imageRaw.cols;
    int hist_h = imageRaw.rows;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                Scalar( 0, 0, 255), 2, 8, 0  );
    }

    namedWindow("calcHist Demo", WINDOW_AUTOSIZE );
    imshow("calcHist Demo", histImage );
}
#define NO_IMAGES 10

/*Open all files in a given path*/
int main()
{

    string images[NO_IMAGES+1];
    vector <Image> vImages;

    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        Mat img_raw;
        stringstream ss;
        string FileName;
        ss << "./training_images/coco_images/coco" <<fileNumber<<".jpg"<<endl;
        ss >> FileName;
        cout << FileName<< endl ;
        img_raw = cv::imread(images[fileNumber],1);
        Image I(img_raw);
        I.FileName = FileName;
        {
            namedWindow("Display Image", WINDOW_AUTOSIZE );
            cv::imshow("Display Image",I.imageRaw);
            waitKey(0);
        }
    }

}
