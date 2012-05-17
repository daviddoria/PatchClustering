#include "PatchClustering.h"


std::vector<float> PatchClustering::ProjectVector(const std::vector<float>& v)
{
  std::vector<float> projected;

  return projected;
}

Eigen::VectorXf PatchClustering::ComputeMeanVector(const EigenHelpers::VectorOfVectors& vectors)
{
  if(vectors.size() == 0)
  {
    throw std::runtime_error("Can't compute the mean of a list of vectors of length zero!");
  }
  // Compute mean vector
  Eigen::VectorXf meanVector = Eigen::VectorXf::Zero(vectors[0].size());
  for(unsigned int i = 0; i < vectors.size(); ++i)
  {
    meanVector += vectors[i];
  }

  meanVector /= vectors.size();

  return meanVector;
}

Eigen::MatrixXf PatchClustering::ConstructCovarianceMatrix(const EigenHelpers::VectorOfVectors& vectors)
{
  if(vectors.size() == 0)
  {
    throw std::runtime_error("Can't compute the covariance matrix of a list of vectors of length zero!");
  }

  Eigen::VectorXf meanVector = ComputeMeanVector(vectors);
  std::cout << "meanVector: " << meanVector << std::endl;

  // Construct covariance matrix
  Eigen::MatrixXf covarianceMatrix = Eigen::MatrixXf::Zero(vectors[0].size(), vectors[0].size());
  std::cout << "covarianceMatrix size: " << covarianceMatrix.rows() << " x " << covarianceMatrix.cols() << std::endl;

  for(unsigned int i = 0; i < vectors.size(); ++i)
  {
    covarianceMatrix += (vectors[i] - meanVector) * (vectors[i] - meanVector).transpose();
  }

  covarianceMatrix /= (vectors.size() - 1);

  return covarianceMatrix;
}
