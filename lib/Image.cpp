#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Image.hpp"

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


