#!/bin/bash

cmake_vars=$1

cmake_build_folder=cmake-build

echo "cmake_vars: $cmake_vars"

#https://stackoverflow.com/questions/1853946/getting-the-last-argument-passed-to-a-shell-script
for last; do true; done
echo "last cmdline arg: $last"

echo "build type: $last"

case $last in
     init)
         mkdir -p $cmake_build_folder && cd $cmake_build_folder && cmake --fresh ..
     ;;
     debug)
         cd $cmake_build_folder && make debug
     ;;
     release)
         cd $cmake_build_folder && make release
     ;;
     clean)
         rm -Rf $cmake_build_folder
     ;;
     help)
         echo "$(basename "$0") <init | debug | release | clean | help>"
     ;;
     *)
       echo "unspecified build type: $last"
     ;;
esac
