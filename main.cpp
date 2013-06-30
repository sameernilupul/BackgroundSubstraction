#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include "SelectROI.h"

#define path "/Volumes/WINDOWS/TestData/5.avi"
#define min_size 500
#define max_size 10000

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat frame;
    Mat back;
    Mat fore;
    Mat frame_roi;
    Rect roi_rect;
    VideoCapture cap(path);
    BackgroundSubtractorMOG2 bg;
    //bg.set("bShadowDetection", false);
    //bg.bShadowDetection = false;
    
    vector<vector<Point> > contours;
    
    namedWindow("Frame");
    namedWindow("Background");
    
    cap >> frame; 
    Rect rect_roi = getSelected(frame);
    
    
    for(;;)
    {
        cap >> frame;           // capture frame from video
        frame_roi = frame(rect_roi);
        bg.operator ()(frame_roi,fore);
        bg.getBackgroundImage(back);    // get background image
        erode(fore,fore,Mat());
        dilate(fore,fore,Mat());
        
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);  // find contours
        
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );
        
        for( int i = 0; i < contours.size(); i++ )
        { 
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }
        
        
        /// Draw polygonal contour + bonding rects + circles
        Mat drawing = Mat::zeros( fore.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ )
        {
            if(boundRect[i].area() <min_size || boundRect[i].area() >max_size){
                continue;
            }
            Scalar color = Scalar( 255,0,0 );
            rectangle( frame_roi, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
            circle( frame_roi, center[i], (int)radius[i], color, 2, 8, 0 );
        }

        
        
        /////
        imshow("Frame",frame);
        imshow("Background",back);
        
        if(waitKey(1) >= 0) break;
    }
    return 0;
}