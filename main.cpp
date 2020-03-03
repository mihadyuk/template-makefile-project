#include "altStitcher.h"
#include "config.h"
#include "tutorialStitcher.h"

int main(int argc, char** argv )
{
#if defined (USE_TUTORIAL_STITCHER)
    tutorial_stitcher(argc, argv);
#elif defined (USE_ALT_STITCHER)
    //alt_stitcher(argc, argv);
#else
#error "unknown stitcher"
#endif
}


