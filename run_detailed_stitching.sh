#!/bin/bash
#set -x

images=$(ls -r --sort=time /tmp/*.jpg)

./build/exec-module-name.elf "$images" --features sift --matcher homography --estimator homography --wave_correct no --save_graph /tmp/match_result --warp spherical --output /tmp/result.jpg 
