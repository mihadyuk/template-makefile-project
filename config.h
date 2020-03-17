/*
 * config.h
 *
 *  Created on: Mar 2, 2020
 *      Author: user
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/**
 * stitcher from tutorial
 *
 * https://docs.opencv.org/4.2.0/d8/d19/tutorial_stitcher.html
 * */
#define USE_TUTORIAL_STITCHER


/**
 * stitcher is based on following links (currently is not finished yet)
 *
 * https://www.pyimagesearch.com/2016/01/11/opencv-panorama-stitching/#download-the-code
 * https://www.pyimagesearch.com/2016/01/11/opencv-panorama-stitching/
 * https://www.pyimagesearch.com/2016/01/25/real-time-panorama-and-image-stitching-with-opencv/
 *
 * */
//#define USE_ALT_STITCHER


/**
 * The same as tutorial. stitcher class copied from opencv 4.2.0 for further modifications
 *
 * */
//#define USE_MY_STITCHER


/**
 * stitching_detailed.cpp. Looks like the same algorithm as opencv stitch class.
 * The stitching detailed contains more cmd line options and enabled logger
 *
 * https://docs.opencv.org/4.2.0/d8/d19/tutorial_stitcher.html
 *
 * */
//#define USE_STITCHING_DETAILED


#endif /* CONFIG_H_ */
