#!/bin/bash

#run stitcher
time ./build/exec-module-name.elf images/bryce_left_01.png images/bryce_right_01.png --output images/my_stitch_result.jpg

#display stitched  image
display images/my_stitch_result.jpg

