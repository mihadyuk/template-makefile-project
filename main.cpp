#include "config.h"
#include "tutorial_stitcher.h"
#include "alt_stitcher.h"

int main(int argc, char** argv )
{
#if defined (USE_TUTORIAL_STITCHER)
    tutorial_stitcher(argc, argv);
#elif defined (USE_ALT_STITCHER)
    alt_stitcher(argc, argv);
#else
#error "unknown stitcher"
#endif
}


