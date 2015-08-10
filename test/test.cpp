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
    /*Coconut tree images*/
    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        Mat img_raw;
        stringstream ss;
        string FileName;
        ss << "../training_images/coco_images/coco" <<fileNumber<<".jpg"<<endl;
        ss >> FileName;
        cout << FileName<< endl ;
        img_raw = cv::imread(FileName,1);
        Image I(img_raw);
        cout << "row*col" << I.g_hist.rows * I.g_hist.cols << endl;
        cout <<"total row * col * 3 " <<I.rawHistData.rows * I.rawHistData.cols << endl;
        I.FileName = FileName;
        I.label = COCONUT;
        vImages.push_back(I);


    }

    for(int fileNumber=1; fileNumber <= NO_IMAGES ; fileNumber++)
    {
        Mat img_raw;
        stringstream ss;
        string FileName;
        ss << "../training_images/non_coco_images/ncoco" <<fileNumber<<".jpg"<<endl;
        ss >> FileName;
        cout << FileName<< endl ;
        img_raw = cv::imread(FileName,1);
        Image I(img_raw);
        cout << "row*col" << I.g_hist.rows * I.g_hist.cols << endl;
        cout <<"total row * col * 3 " <<I.rawHistData.rows * I.rawHistData.cols << endl;
        I.FileName = FileName;
        I.label = NOT_COCONUT;
        vImages.push_back(I);

    }

    vector <Image>::iterator  imageIterator;


    int size=vImages.size();
    float *pfLabels = new float[size]; 
    int i=0;
    for(imageIterator = vImages.begin();imageIterator != vImages.end(); imageIterator++,i++)
    {

        Mat labelMat(1,1,imageIterator->label);

        svmTrainingData.push_back(imageIterator->rawHistData);
        pfLabels[i] = (float)imageIterator->label;


        /*Display images*/
        // if(imageIterator->imageRaw.data != NULL)
        // {
        //     namedWindow("Testimage", WINDOW_AUTOSIZE );
        //     cv::imshow("Testimage",imageIterator->imageRaw);
        //     imageIterator->DisplayHistogram();
        //     waitKey(0);
        // }



    }
    Mat svmTrainingLabel(size,1,CV_32FC1,pfLabels) ;
    cout << "training data dimension" << svmTrainingData.rows << "x" <<  svmTrainingData.cols << endl;
    cout << "training labels dimension" << svmTrainingLabel.rows << "x" <<  svmTrainingLabel.cols << endl;

    CvSVMParams  params;
    params.svm_type = CvSVM::C_SVC;
    params.kernel_type= CvSVM::LINEAR;
    params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER,100,1e-6);
    CvSVM SVM;

    SVM.train(svmTrainingData,svmTrainingLabel,Mat(),Mat(),params);


    vector <Image> vTestImages;
    for(int fileNumber=1; fileNumber <= 14 ; fileNumber++)
    {
        Mat img_raw;
        stringstream ss;
        string FileName;
        ss << "../training_images/test_images/test" <<fileNumber<<".jpg"<<endl;
        ss >> FileName;
        cout << FileName<< endl ;
        img_raw = cv::imread(FileName,1);
        Image I(img_raw);
        I.FileName = FileName;
        int response = SVM.predict(I.rawHistData);
        if(response == COCONUT) 
        {
            cout << "COCONUT" << endl;
        }
        else
        {
            cout << "NOT COCO NUT" << endl;
        }
    }


}
