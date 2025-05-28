#include <iostream>
#include <cstdio>

//#include "qt_subdir/qtexampleskeleton.h"
#include "findsubstring.h"
#include "groupanagrams.h"
#include "lettercombinations.h"
#include "lrucache.h"
#include "reverseint.h"
#include "romantointeger.h"
#include "twosum.h"
#include "binarysearch.h"
#include "slidingwindow.h"
#include "mergeintervals.h"






int main(int argc, char *argv[]) {

    std::cout << "template makefile project \r\n";
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] : \"%s\"\r\n", i, argv[i]);
    }

    LRUCache().run();
    GroupAnagrams().run();
    RomanToInt().run();

    FindSubstring().run();
    LetterCombinations().run();
    TwoSum().run();
    ReverseInt().run();
    BinarySearch().run();
    SlidingWindow().run();
    MergeIntervals().run();


    return 0;
}


