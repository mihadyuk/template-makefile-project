/*
 * alt_stitcher.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: user
 */
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "altStitcher.h"


cv::Mat AltStitcher::detectAndDescribe(const cv::Mat& image) {
    // convert the image to grayscale
    //cv::Mat gray_image;
    //cv::cvtColor(image, gray_image,  cv::ColorConversionCodes::COLOR_BGR2GRAY);

    // detect and extract features from the image
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    sift->detectAndCompute(image, cv::Mat(), keypoints, descriptors);

}


