/*
 * alt_stitcher.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: user
 */
#include <array>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <stddef.h>

#include "altStitcher.h"


AltStitcher::ImageDescriptor AltStitcher::detectAndDescribe(const cv::Mat& image) {
    // convert the image to grayscale
    //cv::Mat gray_image;
    //cv::cvtColor(image, gray_image,  cv::ColorConversionCodes::COLOR_BGR2GRAY);

    // detect and extract features from the image
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    sift->detectAndCompute(image, cv::Mat(), keypoints, descriptors);

    //
    return ImageDescriptor(keypoints, descriptors);
}

AltStitcher::MatchKeypointsResult AltStitcher::matchKeypoints(const ImageDescriptor& imageA, const ImageDescriptor& imageB,
                                                              float ratio, double treshold) {

    // compute the raw matches and initialize the list of actual matches
    cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create();
    std::vector<std::vector<cv::DMatch>> raw_matches;
    matcher->knnMatch(imageA.m_descriptors, imageB.m_descriptors, raw_matches, 2);

    // loop over the raw matches
    std::vector<cv::DMatch> matches;
    cv::Mat homography;
    for (size_t i = 0; i < raw_matches.size(); i++) {
        if (raw_matches[i].size() == 2 && raw_matches[i][0].distance < raw_matches[i][1].distance * ratio) {
            cv::DMatch item;
            item.trainIdx = raw_matches[i][0].trainIdx;
            item.queryIdx = raw_matches[i][0].queryIdx;
            matches.push_back(item);
        }
    }

    // computing a homography between the two sets of points
    if (matches.size() > 4) {
        std::vector<cv::Point2f> ptsA, ptsB;
        for (size_t i = 0; i < matches.size(); i++) {
            ptsA.push_back(imageA.m_keypoints[matches[i].queryIdx].pt);
            ptsB.push_back(imageB.m_keypoints[matches[i].trainIdx].pt);
        }

        homography = cv::findHomography(ptsA, ptsB, cv::RANSAC, treshold);
    }

    return AltStitcher::MatchKeypointsResult(homography, matches);
}





