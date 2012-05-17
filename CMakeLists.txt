cmake_minimum_required(VERSION 2.6)

PROJECT(PatchClustering)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

include_directories(/media/portable/src/Eigen)

# Submodules
add_subdirectory(ITKHelpers)
add_subdirectory(EigenHelpers)

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${USE_ITK_FILE})

ADD_EXECUTABLE(ClusterPatches ClusterPatches.cpp
PatchClustering.cpp)
TARGET_LINK_LIBRARIES(ClusterPatches ${ITK_LIBRARIES} libITKHelpers libEigenHelpers)

ADD_EXECUTABLE(DimensionalityReductionDemo DimensionalityReductionDemo.cpp
PatchClustering.cpp)
TARGET_LINK_LIBRARIES(DimensionalityReductionDemo ${ITK_LIBRARIES} libITKHelpers libEigenHelpers)
