#include <iostream>
#include <cstdio>

//#include "qt_subdir/qtexampleskeleton.h"
#include "findsubstring.h"
#include "groupanagrams.h"
#include "lettercombinations.h"
#include "reverseint.h"
#include "romantointeger.h"
#include "twosum.h"






int main(int argc, char *argv[]) {

    std::cout << "template makefile project \r\n";
    for (int i = 0; i < argc; i++) {
        printf("arg[%d] : \"%s\"\r\n", i, argv[i]);
    }

    GroupAnagrams().run();
    RomanToInt().run();

    FindSubstring().run();
    LetterCombinations().run();
    TwoSum().run();
    ReverseInt().run();


    return 0;
}


