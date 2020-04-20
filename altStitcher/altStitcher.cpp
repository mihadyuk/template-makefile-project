/*
 * alt_stitcher.cpp
 *
 *  Created on: Mar 2, 2020
 *      Author: user
 */
#include <assert.h>
#include <array>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <stddef.h>
#include <stdlib.h>

#include "altStitcher.h"

cv::Mat AltStitcher::stitch(const cv::Mat& imageA, const cv::Mat& imageB, float ratio, double reprojThreshold) {

    auto det_result_a = detectAndDescribe(imageA);
    auto det_result_b = detectAndDescribe(imageB);

    auto match_result = matchKeypoints(det_result_a, det_result_b, ratio, reprojThreshold);

    if (match_result.m_matches.size() == 0)
        return cv::Mat();

    // apply a perspective warp to stitch the images together
    //cv::Mat result(imageA.rows, imageA.cols + imageB.cols, imageA.type());
    cv::Mat result;
    //printf("type before: %d\n", result.type());
    cv::Size size(imageA.cols + imageB.cols, imageA.rows);
    cv::warpPerspective(imageA, result, match_result.m_homography, size);
    // https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv/39780825
    //printf("image type: %d, type after: %d\n", CV_8UC3, result.type());
    assert(result.type() == CV_8UC3);
    assert(imageB.type() == CV_8UC3);

    // create final image.
    // https://stackoverflow.com/questions/6387627/opencv-mat-class-accessing-elements-of-a-multi-channel-matrix
    for (int row = 0; row < imageB.rows; row++) {
      for (int col = 0; col < imageB.cols; col++) {
        result.at<cv::Vec3b>(row, col) = imageB.at<cv::Vec3b>(row, col);
      }
    }

    return result;
}

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
                                                              float ratio, double reprojTreshold) {

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

        homography = cv::findHomography(ptsA, ptsB, cv::RANSAC, reprojTreshold);
    }

    return AltStitcher::MatchKeypointsResult(homography, matches);
}





