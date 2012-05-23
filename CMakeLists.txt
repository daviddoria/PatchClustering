cmake_minimum_required(VERSION 2.6)

PROJECT(PatchClustering)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

include_directories(/media/portable/src/Eigen)

# Submodules
add_subdirectory(KMeansClustering)

if(NOT TARGET ITKHelpers)
  add_subdirectory(ITKHelpers)
endif()

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${USE_ITK_FILE})

add_library(PatchClustering PatchClustering.cpp)
target_link_libraries(PatchClustering KMeansClustering ITKHelpers EigenHelpers)

ADD_EXECUTABLE(ClusterPatches ClusterPatches.cpp)
TARGET_LINK_LIBRARIES(ClusterPatches ${ITK_LIBRARIES} PatchClustering)

ADD_EXECUTABLE(DimensionalityReductionDemo DimensionalityReductionDemo.cpp)
TARGET_LINK_LIBRARIES(DimensionalityReductionDemo ${ITK_LIBRARIES} PatchClustering)
