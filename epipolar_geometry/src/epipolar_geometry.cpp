/**
 * @file epipolar_geometry.cpp
 * 
 * @brief Calculate disparity map for a pair of images using StereoSGBM
 * 
 * @author M Talha
 */

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Load pair of images
    cv::Mat left_img, right_img;
    cv::String img_path = "../../../epipolar_geometry/images/";
    left_img = cv::imread(img_path+"img0.png", 0);
    right_img = cv::imread(img_path+"img1.png", 0);

    cv::resize(left_img, left_img, cv::Size(800, 600));
    cv::resize(right_img, right_img, cv::Size(800, 600));

    // Set parameters for StereoSGBM algorithm
    int minDisparity = 0;
    int numDisparities = 64;
    int blockSize = 8;
    int disp12MaxDiff = 1;
    int uniquenessRatio = 10;
    int speckleWindowSize = 10;
    int speckleRange = 8;

    // Create StereoSGBM object
    cv::Ptr<cv::StereoSGBM> stereo_SGBM = cv::StereoSGBM::create(
        minDisparity,numDisparities, blockSize, 0, 0, disp12MaxDiff, 
        0, uniquenessRatio, speckleWindowSize, speckleRange);

    // Compute disparity map for image pair
    cv::Mat disp;
    stereo_SGBM->compute(left_img, right_img, disp);

    // Normalise disparity map between [0, 255] for better visuals
    cv::normalize(disp, disp, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    cv::imshow("Left Image", left_img);
    cv::imshow("Right Image", right_img);
    // Lighter pixels are closer than darker pixels
    cv::imshow("Disparity map", disp);
    cv::waitKey();

    return 0;
}
