cmake_minimum_required(VERSION 3.28)

#https://stackoverflow.com/questions/10083427/can-cmake-generate-a-single-makefile-that-supports-both-debug-and-release
ADD_CUSTOM_TARGET(debug
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Creating the executable in the debug mode.")

ADD_CUSTOM_TARGET(release
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Creating the executable in the release mode.")

#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")

# this statement set(CMAKE_CXX_STANDARD 20) turned into -std=gnu++20 option
# if it is needed to specify c++20 without gnu extensions,
# 1. comment out set(CMAKE_CXX_STANDARD 20) and set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 2. add -std=c++20 into add_compile_options statement
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(template-makefile-project
        VERSION 1.0
        DESCRIPTION "cmake project template"
        LANGUAGES CXX C)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE)
	string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

	if (build_type STREQUAL debug)
		message(STATUS "debug compile options")
		# todo: fix duplicated -O -g options
		add_compile_options(-O0 -g3 -pedantic -Wall -fmessage-length=0)
	elseif (build_type STREQUAL release)
		message(STATUS "release compile options")
		# todo: fix duplicated -O options
		add_compile_options(-O2 -g3 -pedantic -Wall -fmessage-length=0)
	else()
	        add_compile_options(-O0 -g3 -pedantic -Wall -fmessage-length=0)
	endif()
else()
	message(STATUS "CMAKE_BUILD_TYPE is not set")
	add_compile_options(-O0 -g3 -pedantic -Wall -fmessage-length=0)
endif()



file(GLOB SRC_LIST *.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SRC_LIST})

get_target_property(TARGET_COMPILE_OPTIONS ${CMAKE_PROJECT_NAME} COMPILE_OPTIONS)
message(STATUS "Compile options: ${TARGET_COMPILE_OPTIONS}")

