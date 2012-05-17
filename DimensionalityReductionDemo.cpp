// STL
#include <iostream>

// Submodules
#include "EigenHelpers/EigenHelpers.h"

// Eigen
#include <Eigen/Dense>

int main(int argc, char*argv[])
{
  EigenHelpers::VectorOfVectors vectors;

  // Create 4 points on a line
  Eigen::Vector2f v;
  v[0] = 1; v[1] = 1;
  vectors.push_back(v);
  v[0] = 2; v[1] = 2;
  vectors.push_back(v);
  v[0] = 5; v[1] = 5;
  vectors.push_back(v);
  v[0] = 8; v[1] = 7; // This point is not exactly on the line, to add a bit of noise
  vectors.push_back(v);

  std::cout << "Original vectors:" << std::endl;
  EigenHelpers::OutputVectors(vectors);

  // Project the points onto the new basis. These projected values should simply be the distance from the origin along
  // the best fit line through the original points (which is essentially the line y=x)
  EigenHelpers::VectorOfVectors projectedVectors = EigenHelpers::DimensionalityReduction(vectors, 1);
  for(unsigned int i = 0; i < vectors.size(); ++i)
  {
    std::cout << projectedVectors[i] << std::endl;
  }

  return EXIT_SUCCESS;
}
