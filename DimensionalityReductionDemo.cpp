// STL
#include <iostream>

// Custom
#include "PatchClustering.h"

// Submodules
#include "EigenHelpers/EigenHelpers.h"

// Eigen
#include <Eigen/Dense>

int main(int argc, char*argv[])
{
  
  EigenHelpers::VectorOfVectors vectors;

  PatchClustering patchClustering;
  
  // Create 4 points on a line
  Eigen::Vector2f v;
  v[0] = 1; v[1] = 1;
  vectors.push_back(v);
  v[0] = 2; v[1] = 2;
  vectors.push_back(v);
  v[0] = 5; v[1] = 5;
  vectors.push_back(v);
  v[0] = 8; v[1] = 7;
  vectors.push_back(v);

  std::cout << "Original vectors:" << std::endl;
  EigenHelpers::OutputVectors(vectors);
  
  Eigen::MatrixXf covarianceMatrix = patchClustering.ConstructCovarianceMatrix(vectors);
  std::cout << "covarianceMatrix: " << covarianceMatrix << std::endl;

  typedef Eigen::JacobiSVD<Eigen::MatrixXf> SVDType;
  SVDType svd(covarianceMatrix, Eigen::ComputeFullU | Eigen::ComputeFullV);
  std::cout << "U: " << svd.matrixU() << std::endl;
  std::cout << "V: " << svd.matrixV() << std::endl;

  SVDType::SingularValuesType singularValues = svd.singularValues();
  for(int i = 0; i < singularValues.size(); ++i)
  {
    std::cout << "singular value " << i << " : " << singularValues[i] << std::endl;
  }

  // Only keep the first N singular vectors of U
  Eigen::MatrixXf truncatedU = EigenHelpers::TruncateColumns(svd.matrixU(), 1);
  EigenHelpers::OutputMatrixSize(truncatedU);
  
  // Project the points onto the new basis
  for(unsigned int i = 0; i < vectors.size(); ++i)
  {
    std::cout << truncatedU.transpose() * vectors[i] << std::endl;
  }
  
  return EXIT_SUCCESS;
}
