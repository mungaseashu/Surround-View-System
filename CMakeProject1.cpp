// Bosch AutoVision X Hackathon Solution for Image Stitching Problem in C++.
// Group Members (Team Spirit): 
// Pradip Warkhade, TY-IT (SCOE, Kopargaon)
// Kaveri Mungase, TY-IT (SCOE, Kopargaon)

#include <iostream>  // For input/output operations
#include <opencv2/opencv.hpp>  // For OpenCV functionalities
#include <opencv2/highgui/highgui.hpp>  // For GUI operations like image display
#include <opencv2/imgproc/imgproc.hpp>  // For image processing operations
#include <vector>  // For using vectors

/**
 * @brief Finds the contour with the maximum area from a vector of contours.
 *
 * This function efficiently iterates through all contours in the given vector
 * and calculates their area using `cv::contourArea`. It updates the maximum area
 * and its corresponding index if a larger area is encountered.
 *
 * @param contours Vector containing contours.
 * @return Index of the contour with the maximum area.
 */
int findMaxAreaContour(const std::vector<std::vector<cv::Point>>& contours) {
    double maxArea = -1;
    int maxAreaIndex = -1;
    for (int i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaIndex = i;
        }
    }
    return maxAreaIndex;
}

/**
 * @brief Main function for image stitching process and ROI extraction.
 *
 * This function reads a set of images using a glob pattern, stitches them
 * together using cv::Stitcher, performs image processing to refine the result,
 * extracts the Region of Interest (ROI) based on the largest contour, and
 * finally saves the processed image.
 *
 * @return 0 upon successful execution, -1 otherwise.
 */
int main() {

    // Glob and read images
    std::vector<cv::String> image_paths;
    cv::glob("D:/Sanjivani/B Tech 3rd Year/Sem 2/Bosch/CMakeProject1/CMakeProject1/ok1/*.jpg", image_paths);
    std::vector<cv::Mat> images;

    // Read and display each image
    for (const auto& image_path : image_paths) {
        cv::Mat img = cv::imread(image_path);
        images.push_back(img);
        cv::imshow("Image", img);
        cv::waitKey(0);
    }

    // Configure stitcher 
    // Should perform stitching to create a panoramic image.
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
    cv::Ptr<cv::Stitcher> imageStitcher = cv::Stitcher::create(mode);

    // Configure and run image stitching
    imageStitcher->setWaveCorrection(true); // Enable wave correction
    imageStitcher->setWaveCorrectKind(cv::detail::WAVE_CORRECT_HORIZ); // Horizontal wave correction
    imageStitcher->setRegistrationResol(1.4); // Adjust resolution for registration
    imageStitcher->setSeamEstimationResol(2); // Adjust resolution for seam estimation
    imageStitcher->setCompositingResol(10); // Adjust resolution for compositing
    imageStitcher->setPanoConfidenceThresh(1); // Set confidence threshold for panorama

    // Stitch the images
    cv::Mat stitched_image;
    cv::Stitcher::Status status = imageStitcher->stitch(images, stitched_image);

    // Check if stitching was successful
    if (status == cv::Stitcher::Status::OK) {
        // Save and display the stitched image
        cv::imwrite("D:/Sanjivani/B Tech 3rd Year/Sem 2/Bosch/CMakeProject1/CMakeProject1/Result_image.jpg", stitched_image);
        cv::imshow("Stitched Image", stitched_image);
        cv::waitKey(0);

        // Add border to stitched image
        cv::copyMakeBorder(stitched_image, stitched_image, 10, 10, 10, 10, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));

        // Convert to grayscale
        cv::Mat gray;
        cv::cvtColor(stitched_image, gray, cv::COLOR_BGR2GRAY);

        // Threshold image
        cv::Mat thresh_img;
        cv::threshold(gray, thresh_img, 0, 255, cv::THRESH_BINARY);

        // Display threshold image
        cv::imshow("Threshold Image", thresh_img);
        cv::waitKey(0);

        // Find contours
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(thresh_img.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Find the contour with the maximum area
        int maxAreaIndex = findMaxAreaContour(contours);

        // Create a mask around the largest contour
        cv::Mat mask = cv::Mat::zeros(thresh_img.size(), CV_8UC1);
        cv::Rect boundingRect = cv::boundingRect(contours[maxAreaIndex]);
        cv::rectangle(mask, boundingRect, 255, -1);

        // Erode the mask until it's empty
        cv::Mat minRectangle = mask.clone();
        cv::Mat sub = mask.clone();
        int prevNonZeroCount = cv::countNonZero(sub);

        while (true) {
            cv::erode(minRectangle, minRectangle, cv::Mat());
            cv::subtract(minRectangle, thresh_img, sub);
            int currentNonZeroCount = cv::countNonZero(sub);

            // Check if no change in non-zero count, break the loop
            if (currentNonZeroCount == prevNonZeroCount) {
                break;
            }
            prevNonZeroCount = currentNonZeroCount;
        }

        // Find contours again in the eroded mask
        contours.clear();
        cv::findContours(minRectangle.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Find the contour with the maximum area in the new mask
        maxAreaIndex = findMaxAreaContour(contours);

        // Get the bounding rectangle and extract the Region of Interest (ROI) from the stitched image
        boundingRect = cv::boundingRect(contours[maxAreaIndex]);
        stitched_image = stitched_image(boundingRect);

        // Save the processed stitched image
        cv::imwrite("D:/Sanjivani/B Tech 3rd Year/Sem 2/Bosch/CMakeProject1/CMakeProject1/Final_output.jpg", stitched_image);

        // Display the processed stitched image
        cv::imshow("Stitched Image Processed", stitched_image);
        cv::waitKey(0);
    }
    else {
        // Handle the case where stitching was not successful
        std::cout << "Images could not be stitched!" << std::endl;
        std::cout << "Likely not enough keypoints being detected!" << std::endl;
    }

    return 0; // Return 0 to indicate successful execution of the program
}
