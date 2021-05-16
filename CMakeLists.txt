cmake_minimum_required(VERSION 3.20.0)
project(LearnOpenCV)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-W4")
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EHsc")
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(opencv_install)
add_subdirectory(camera_calibration)
add_subdirectory(epipolar_geometry)
