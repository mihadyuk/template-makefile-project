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
 * */
class AltStitcher {
public:

private:
    struct ImageDescriptor {
        std::vector<cv::KeyPoint> m_keypoints;
        cv::Mat m_descriptors;

        ImageDescriptor(const std::vector<cv::KeyPoint>& keypoints, const cv::Mat& descriptors) :
            m_keypoints(keypoints),
            m_descriptors(descriptors)
        {}
    };

    ImageDescriptor detectAndDescribe(const cv::Mat& image);
};


#endif /* ALTSTITCHER_H_ */
