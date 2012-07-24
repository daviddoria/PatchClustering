cmake_minimum_required(VERSION 2.6)

PROJECT(PatchClustering)

# This is needed for c++11 usage in Helpers subsubmodule
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

include_directories(/media/portable/src/Eigen)

# Submodules
add_subdirectory(KMeansClustering)

if(NOT TARGET ITKHelpers)
  add_subdirectory(ITKHelpers)
  include_directories(${ITKHelpers_includes})
endif()

FIND_PACKAGE(ITK REQUIRED ITKCommon ITKIOImageBase
            ITKImageIntensity ITKImageFeature ITKMathematicalMorphology ITKBinaryMathematicalMorphology)
INCLUDE(${USE_ITK_FILE})

if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
  set(PatchClustering_includes ${ITKHelpers_includes} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
endif()

add_library(PatchClustering PatchClustering.cpp)
target_link_libraries(PatchClustering KMeansClustering ITKHelpers EigenHelpers)

SET(PatchClustering_BuildExamples OFF CACHE BOOL "PatchClustering_BuildExamples")
if(PatchClustering_BuildExamples)

  ADD_EXECUTABLE(ClusterPatches ClusterPatches.cpp)
  TARGET_LINK_LIBRARIES(ClusterPatches ${ITK_LIBRARIES} PatchClustering)

  ADD_EXECUTABLE(DimensionalityReductionDemo DimensionalityReductionDemo.cpp)
  TARGET_LINK_LIBRARIES(DimensionalityReductionDemo ${ITK_LIBRARIES} PatchClustering)

endif(PatchClustering_BuildExamples)

