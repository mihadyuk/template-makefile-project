#!/bin/bash

cmake_vars=$1

cmake_build_folder=cmake-build

echo "cmake_vars: $cmake_vars"

#https://stackoverflow.com/questions/1853946/getting-the-last-argument-passed-to-a-shell-script
for last; do true; done
echo "last cmdline arg: $last"

echo "build type: $last"

case $last in
     all)
         mkdir -p $cmake_build_folder && cd $cmake_build_folder && cmake --fresh .. && make
     ;;
     clean)
         rm -Rf $cmake_build_folder
     ;;
     help)
         echo "$(basename "$0") <all | clean | help>"
     ;;
     *)
       echo "unspecified build type: $last"
     ;;
esac
