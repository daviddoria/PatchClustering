// STL
#include <iostream>

// ITK
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkPasteImageFilter.h"
#include "itkCovariantVector.h"

// Submodules
#include "ITKHelpers/ITKHelpers.h"
#include "KMeansClustering/KMeansClustering.h"

#include "PatchClustering.h"

typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> ImageType;
typedef itk::Image<float, 2> FloatImageType;

void CreateImage(ImageType* const image);

int main(int argc, char*argv[])
{
//   if(argc < 2)
//   {
//     std::cerr << "Required arguments: image.png" << std::endl;
//     return EXIT_FAILURE;
//   }
//   
//   std::string inputFileName = argv[1];
// 
//   std::cout << "inputFileName: " << inputFileName << std::endl;
// 
//   typedef itk::ImageFileReader<ImageType> ReaderType;
// 
//   ReaderType::Pointer reader = ReaderType::New();
//   reader->SetFileName(inputFileName);
//   reader->Update();
//   ImageType* image = reader->GetOutput();

  ImageType::Pointer generatedImage = ImageType::New();
  CreateImage(generatedImage);

  ImageType* image = generatedImage.GetPointer(); // This is done so that the reader->GetOutput() type will match (so we can switch to reading a real input image later)
  
  PatchClustering patchClustering; // An object to use to call the functions.
  
  itk::ImageRegionIterator<ImageType> imageIterator(image,
                                                    image->GetLargestPossibleRegion());
  std::cout << "Iterating over " << image->GetLargestPossibleRegion() << std::endl;

  unsigned int patchRadius = 5;

  EigenHelpers::VectorOfVectors vectors;
  std::vector<itk::ImageRegion<2> > regions;
  
  while(!imageIterator.IsAtEnd())
    {
    itk::ImageRegion<2> region = ITKHelpers::GetRegionInRadiusAroundPixel(imageIterator.GetIndex(), patchRadius);

    if(image->GetLargestPossibleRegion().IsInside(region))
      {
      Eigen::VectorXf v = patchClustering.VectorizePatch(image, region);

      vectors.push_back(v);
      regions.push_back(region);
      }
    ++imageIterator;
    }

  std::cout << "There are " << regions.size() << " regions." << std::endl;

  EigenHelpers::VectorOfVectors projectedVectors = EigenHelpers::DimensionalityReduction(vectors, 10);

  KMeansClustering kmeans;
  kmeans.SetK(2);
  kmeans.SetPoints(projectedVectors);
  kmeans.SetInitMethod(KMeansClustering::KMEANSPP);
  //kmeans.SetRandom(false); // for repeatable results
  kmeans.SetRandom(true); // for real, random results
  kmeans.Cluster();

  std::vector<unsigned int> labels = kmeans.GetLabels();

  std::cout << "Resulting cluster ids:" << std::endl;
  for(unsigned int i = 0; i < labels.size(); ++i)
  {
    std::cout << labels[i] << std::endl;
  }
  /*
  typedef  itk::ImageFileWriter< ImageType  > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName(outputFilename);
  writer->SetInput(output);
  writer->Update();
  */

  return EXIT_SUCCESS;
}

void CreateImage(ImageType* const image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(20);

  ImageType::RegionType region(start,size);
  image->SetRegions(region);
  image->Allocate();

  itk::ImageRegionIterator<ImageType> imageIterator(image, region);

  ImageType::PixelType black;
  black.Fill(0);

  ImageType::PixelType white;
  white.Fill(255);
  
  while(!imageIterator.IsAtEnd())
    {
    if(imageIterator.GetIndex()[0] < static_cast<int>(size[0]/2))
      {
      imageIterator.Set(black);
      }
    else
      {
      imageIterator.Set(white);
      }

    ++imageIterator;
    }

}
