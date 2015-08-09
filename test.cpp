/**
 * @file test.cpp
 * @brief  Test app
 * @author Vikas MK
 * @version 1.3
 * @date 2015-08-07
 */

/*Revision history*/
/*1.0 : Created */
/*1.1 : Added Image class and methods. Compiles, doesnt' work */
/*1.2 : Compiles and displays test images. Histogram part is buggy*/
/*1.3 : calculates and displays Histograms correctly*/
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace std;
using namespace cv;
#define NO_OF_BINS 256

class Image
{
    private:
        float range[2];
        vector<Mat> bgrPlanes; /*Histogram will be split into rgb subspace*/
        Mat b_hist,r_hist,g_hist; /*histogram of all 3 channels*/
        int histSize ;/*Size of histogram*/
        const float* histRange;
    public:
        Mat imageRaw;
        string FileName;
        Image(void);
        Image(Mat aMat); /*Initializes the image info, and calculates histogram*/
        void DisplayHistogram(void);
};


Image::Image(Mat aMat)
{
    histSize = NO_OF_BINS;
    /*Copy to imageRaw*/
    imageRaw = aMat.clone();

    cv::split(imageRaw,bgrPlanes);

    range[0] = 0;
    range[1] = NO_OF_BINS;

    histRange =  range ;
    cv::calcHist(&bgrPlanes[0],1,0,Mat(),b_hist,1,&histSize,&histRange,true,false);
    cv::calcHist(&bgrPlanes[1],1,0,Mat(),g_hist,1,&histSize,&histRange,true,false);
    cv::calcHist(&bgrPlanes[2],1,0,Mat(),r_hist,1,&histSize,&histRange,true,false);
}

void Image::DisplayHistogram(void)
{
    int hist_w = 200;//;imageRaw.cols;
    int hist_h = 200;//imageRaw.rows;
    int bin_w = cvRound( (double) hist_w/histSize );

    cout << "bin_w" << bin_w << endl;

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

    namedWindow("Histogram", WINDOW_AUTOSIZE );
    imshow("Histogram", histImage );
}

#define NO_IMAGES 10

/*Open all files in a given path*/
int main()
{
    vector <Image> vImages;

    /*Read images from files and add it into a vector*/
    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        Mat img_raw;
        stringstream ss;
        string FileName;
        ss << "./training_images/coco_images/coco" <<fileNumber<<".jpg"<<endl;
        ss >> FileName;
        cout << FileName<< endl ;
        img_raw = cv::imread(FileName,1);
        Image I(img_raw);
        I.FileName = FileName;
        vImages.push_back(I);
    }

    /*Display vectors*/
    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        if(vImages[fileNumber-1].imageRaw.data != NULL)
        {
            namedWindow("Testimage", WINDOW_AUTOSIZE );
            cv::imshow("Testimage",vImages[fileNumber-1].imageRaw);
            cout << "rows:" << vImages[fileNumber-1].imageRaw.rows << endl;
            cout << "cols:" << vImages[fileNumber-1].imageRaw.cols << endl;
            vImages[fileNumber-1].DisplayHistogram();
            waitKey(0);
        }
    }
}
