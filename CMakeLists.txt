cmake_minimum_required(VERSION 2.6)

PROJECT(PatchClustering)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

include_directories(/media/portable/src/Eigen)

# Submodules
add_subdirectory(KMeansClustering)

if(NOT TARGET ITKHelpers)
  add_subdirectory(ITKHelpers)
endif()

if(NOT TARGET EigenHelpers)
  add_subdirectory(EigenHelpers)
endif()

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${USE_ITK_FILE})

ADD_EXECUTABLE(ClusterPatches ClusterPatches.cpp
PatchClustering.cpp)
TARGET_LINK_LIBRARIES(ClusterPatches ${ITK_LIBRARIES} ITKHelpers EigenHelpers KMeansClustering)

ADD_EXECUTABLE(DimensionalityReductionDemo DimensionalityReductionDemo.cpp
PatchClustering.cpp)
TARGET_LINK_LIBRARIES(DimensionalityReductionDemo ${ITK_LIBRARIES} ITKHelpers EigenHelpers)
