/*
 * config.h
 *
 *  Created on: Mar 2, 2020
 *      Author: user
 */

#ifndef CONFIG_H_
#define CONFIG_H_

//#define USE_TUTORIAL_STITCHER
#define USE_ALT_STITCHER



#if defined(USE_TUTORIAL_STITCHER) && defined (USE_ALT_STITCHER)
#error "one sticher shall be enabled at the same time."
#endif


#endif /* CONFIG_H_ */
