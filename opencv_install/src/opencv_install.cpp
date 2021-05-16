/**
 * @file opencv_install.cpp
 * 
 * @brief Quick test using edge detection to see if OpenCV installed correctly. 
 * 
 * @author M Talha
 */

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    printf("Using OpenCV version %s. \n", cv::getVersionString().c_str());
    
    VideoCapture capture(0);
    Mat gray,edge;
    while(1)
    {
        Mat frame;
        capture >> frame;
        printf("Camera capturing....\n");

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        blur(gray, edge, Size(3,3));
        Canny(edge, edge, 3, 9);

        imshow("Capture",edge);
        waitKey(30);
    }
    return 0;
}