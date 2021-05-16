/**
 * @file camera_calibration.cpp
 * 
 * @brief Use checkerboard images to determine camera intinsic and extrinsic
 * matrices. Use of calibration matrices to undistort images.
 * 
 * @author M Talha
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d_c.h> // FindChessboard flags

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/**
 * Get path to current working directory as a string
 */
std::string GetCWD() {
   char buff[FILENAME_MAX]; // create string buffer to hold path
   GetCurrentDir( buff, FILENAME_MAX ); // get path to dir
   std::string current_working_dir(buff);
   return current_working_dir;
}

/**
 * Get the path for all .jpg images in a directory 
 */
void GetImagePaths(std::vector<cv::String> &images) {
    // Folder containing checkerboard images
    std::string path = "../../../camera_calibration/images/*.jpg";
    // Store path to all images in folder
    cv::glob(path, images);
}

// Driver code
int main()
{
    const cv::Size kCheckerboard = cv::Size(6, 9);
    // Current path is the binary folder
    std::cout << GetCWD() << '\n';

    // Store path for images
    std::vector<cv::String> images;
    GetImagePaths(images);

    // Define the world coordinates for 3D points
    std::vector<cv::Point3f> obj_pts;
    for (int i = 0; i < kCheckerboard.height; i++)
    {
        for (int j = 0; j < kCheckerboard.width; j++)
        {
            // Store in column-major order for findChessboardCorners compatibility
            obj_pts.push_back(cv::Point3f((float)j, (float)i, 0));
        }
    }

    // Vector to store 3D points for each image
    std::vector<std::vector<cv::Point3f> > object_pts;
    // Vector to store corresponding 2D points for each image
    std::vector<std::vector<cv::Point2f> > image_pts;
    
    // Vector to store pixel coordinates of detected corners 
    std::vector<cv::Point2f> corner_pts;
    cv::Mat img;
    bool success;
    // Loop over all images
    for (size_t i = 0; i < images.size(); i++)
    {
        // Read image as greyscale
        img = cv::imread(images[i], cv::IMREAD_GRAYSCALE);
        // Find chessboard corners
        success = cv::findChessboardCorners(img, kCheckerboard, corner_pts, 
            CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
        // if corners found, refine their pixel coordinates
        if (success) {
            // Define termination criteria for corner refinement
            cv::TermCriteria criteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.001);
            // Iteratively refine corner coordinates to subpixel level accuracy
            cv::cornerSubPix(img, corner_pts, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            // Store the world-image corresponding point pairs for the image
            object_pts.push_back(obj_pts);
            image_pts.push_back(corner_pts);
        }
        
        // Visualise corners
        cv::drawChessboardCorners(img, kCheckerboard, corner_pts, success);

        // cv::imshow("Image", img);
        // cv::waitKey(0);
    }

    cv::destroyAllWindows();

    // Calibrate camera using the 3D world points and corresponding pixel 
    // coordinates of detected corners
    cv::Mat camera_matrix, distortion_coeffs, rotation_vec, translation_vec;
    cv::calibrateCamera(object_pts, image_pts, cv::Size(img.rows, img.cols), 
        camera_matrix, distortion_coeffs, rotation_vec, translation_vec);

    std::cout << "cameraMatrix : " << camera_matrix << '\n';
    std::cout << "Distortion coeffcients : " << distortion_coeffs << '\n';
    std::cout << "Rotation vector : " << rotation_vec << '\n';
    std::cout << "Translation vector : " << translation_vec << '\n';



    // Undistort the images using the camera parameters obtained from calibration
    // Get an image
    cv::Mat image = cv::imread(images[0]);
    cv::Size img_size = cv::Size(image.cols, image.rows);

    // Refine the camera matrix using calibration parameters
    cv::Mat new_camera_matrix = cv::getOptimalNewCameraMatrix(camera_matrix, 
        distortion_coeffs, img_size, 1, img_size, 0);
    
    // Method 1 to undistort the image
    cv::Mat undistorted_image;
    cv::undistort(image, undistorted_image, new_camera_matrix, distortion_coeffs, new_camera_matrix);

    // Display the undistorted image
    cv::imshow("Distorted image", cv::imread(images[0]));
    cv::imshow("Undistorted image", undistorted_image);
    cv::waitKey(0);

    // Method 2 to undistort the image
    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(camera_matrix, distortion_coeffs, cv::Mat(), 
        new_camera_matrix, img_size, CV_16SC2, map1, map2);
    cv::remap(cv::imread(images[0]), undistorted_image, map1, map2, cv::INTER_LINEAR);

    // Display the undistorted image
    cv::imshow("Distorted image 2", cv::imread(images[0]));
    cv::imshow("Undistorted image 2", undistorted_image);
    cv::waitKey(0);

    return 0;
}
