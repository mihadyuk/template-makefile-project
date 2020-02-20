ifeq ($(PROJECT),)
	PROJECT	= exec-module-name
endif
#DISABLE_ASSERTS		= yes
#GPROF_EN = yes
#LST_FILE_GEN = yes
#DMP_FILE_GEN = yes
#ASM_LST_FILE_GEN = yes
#MAP_FILE_GEN     = yes
#USE_VERBOSE_COMPILE = yes

#include dirs
INCDIR = .\
         src \
         /usr/include/opencv4

# C source files
CSRC = $(wildcard src/*.c) \
       $(wildcard ./*.c) \

# CPP source files
CPPSRC = $(wildcard ./*.cpp) \
         $(wildcard src/*.cpp) \

#asm source files
ASSRC = $(wildcard ./*.S)

ifeq ($(LIBDIR),)
    LIBDIR  = /usr/lib
endif

#used libs
#ULIBS = config++ pthread
ifeq ($(ULIBS),)
	ULIBS = opencv_gapi opencv_stitching opencv_aruco opencv_bgsegm \
	        opencv_bioinspired opencv_ccalib opencv_cvv opencv_dnn_objdetect \
	        opencv_dnn_superres opencv_dpm opencv_highgui opencv_face opencv_freetype \
	        opencv_fuzzy opencv_hdf opencv_hfs opencv_img_hash opencv_line_descriptor \
	        opencv_quality opencv_reg opencv_rgbd opencv_saliency opencv_stereo opencv_structured_light \
	        opencv_phase_unwrapping opencv_superres opencv_optflow opencv_surface_matching opencv_tracking \
	        opencv_datasets opencv_text opencv_dnn opencv_plot opencv_videostab opencv_videoio opencv_viz \
	        opencv_xfeatures2d opencv_shape opencv_ml opencv_ximgproc opencv_video opencv_xobjdetect \
	        opencv_objdetect opencv_calib3d opencv_imgcodecs opencv_features2d opencv_flann opencv_xphoto opencv_photo opencv_imgproc opencv_core
endif	


CPPC = $(CCACHE) $(CROSS_COMPILE)g++
CC   = $(CCACHE) $(CROSS_COMPILE)gcc
AS   = $(CCACHE) $(CROSS_COMPILE)as
LD   = $(CCACHE) $(CROSS_COMPILE)g++
OD   = $(CCACHE) $(CROSS_COMPILE)objdump
SZ   = $(CCACHE) $(CROSS_COMPILE)size
AR   = $(CCACHE) $(CROSS_COMPILE)ar


#c specific options
ifeq ($(COPT),)
	COPT = -O0 -g3 -Wall -fmessage-length=0
endif	

#c++ specific options
ifeq ($(CPPOPT),)
	CPPOPT = -std=c++0x -O0 -g3 -Wall -fmessage-length=0
endif	

#asm options
ifeq ($(ASOPT),)
	ASOPT = 
endif	


#linker options
ifeq ($(LDOPT),)
	LDOPT =
endif	
	 


include rules.mk