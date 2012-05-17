cmake_minimum_required(VERSION 2.6)

PROJECT(PatchClustering)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

include_directories(/media/portable/src/Eigen)

add_subdirectory(ITKHelpers)

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${USE_ITK_FILE})

ADD_EXECUTABLE(PatchClustering PatchClustering.cpp)
TARGET_LINK_LIBRARIES(PatchClustering ${ITK_LIBRARIES} libITKHelpers)
