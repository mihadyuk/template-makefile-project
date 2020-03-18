/*
 * alt_stitcher.h
 *
 *  Created on: Mar 2, 2020
 *      Author: user
 */
#ifndef ALTSTITCHER_H_
#define ALTSTITCHER_H_

#include <vector>
#include <opencv2/core/mat.hpp>

/**
 * https://www.pyimagesearch.com/2016/01/25/real-time-panorama-and-image-stitching-with-opencv/
 * https://www.pyimagesearch.com/2016/01/11/opencv-panorama-stitching/
 *
 * @TODO implement drawMatches
 * */
class AltStitcher {
public:
    void stitch(const cv::Mat& imageA, const cv::Mat& imageB, float ratio=0.75, double reprojThreshold = 4.0);
private:
    struct ImageDescriptor {
        ImageDescriptor(const std::vector<cv::KeyPoint>& keypoints, const cv::Mat& descriptors) :
                    m_keypoints(keypoints),
                    m_descriptors(descriptors)
        {}

        std::vector<cv::KeyPoint> m_keypoints;
        cv::Mat m_descriptors;
    };

    struct MatchKeypointsResult {
        MatchKeypointsResult(const cv::Mat& homography, const std::vector<cv::DMatch>& matches) :
            m_homography(homography),
            m_matches(matches)
        {}

        cv::Mat m_homography;
        std::vector<cv::DMatch> m_matches;
    };

    ImageDescriptor detectAndDescribe(const cv::Mat& image);

    MatchKeypointsResult matchKeypoints(const ImageDescriptor& imageA, const ImageDescriptor& imageB,
                                        float ratio, double reprojTreshold);
};


#endif /* ALTSTITCHER_H_ */
