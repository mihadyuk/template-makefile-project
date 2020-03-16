#include "config.h"
#include "myStitcherMain.h"
#include "stitchingDetailedMain.h"
#include "tutorialStitcherMain.h"

int main(int argc, char** argv )
{
#if defined (USE_TUTORIAL_STITCHER)
    tutorialStitcherMain(argc, argv);
#elif defined (USE_ALT_STITCHER)
#error "alternate stitcher is not implemented yet"
#elif defined(USE_MY_STITCHER)
    myStitcherMain(argc, argv);
#elif defined (USE_STITCHING_DETAILED)
    stitchingDetailedMain(argc, argv);
#else
#error "unknown stitcher"
#endif
}


