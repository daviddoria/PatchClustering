#ifndef PatchClustering_H
#define PatchClustering_H

// ITK
#include "itkVectorImage.h"

// Eigen
#include <Eigen/Dense>

// Submodules
#include "EigenHelpers/EigenHelpers.h"

class PatchClustering
{
public:

  template <typename TImage>
  std::vector<float> VectorizePatch(const TImage* const image, const itk::ImageRegion<2>& region);


};

#include "PatchClustering.hpp"

#endif
