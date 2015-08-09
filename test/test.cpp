/**
** @file test.cpp
** @brief  Test app
** @author Vikas MK
** @version 1.3
** @date 2015-08-07
**/

/*Revision history*/
/*1.0 : Created */
/*1.1 : Added Image class and methods. Compiles, doesnt' work */
/*1.2 : Compiles and displays test images. Histogram part is buggy*/
/*1.3 : calculates and displays Histograms correctly*/
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>

#include "../lib/Image.hpp"
using namespace std;
using namespace cv;



#define NO_IMAGES 10

/*Open all files in a given path*/
int main()
{
    vector <Image> vImages;

   Mat svmTrainingData;
   int svmlabels;
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
        cout << "row*col" << I.g_hist.rows * I.g_hist.cols << endl;
        cout <<"total row * col * 3 " <<I.rawHistData.rows * I.rawHistData.cols << endl;
        I.FileName = FileName;
        vImages.push_back(I);


    }

   vector <Image>::iterator  imageIterator;

   for(imageIterator = vImages.begin();imageIterator != vImages.end(); imageIterator++)
   {

       svmTrainingData.push_back(imageIterator->rawHistData);

       /*Display images*/
       if(imageIterator->imageRaw.data != NULL)
       {
           namedWindow("Testimage", WINDOW_AUTOSIZE );
           cv::imshow("Testimage",imageIterator->imageRaw);
           imageIterator->DisplayHistogram();
           waitKey(0);
       }

       /*Copy rgb historgram data into plain arraws
        * If there are N images, that would be N rows of rgb histogram data  
        * Note: when copying data form a Mat object to a normal*/


   }
   cout << "training data dimension" << svmTrainingData.rows * svmTrainingData.cols << endl;
}

