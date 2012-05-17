#include "PatchClustering.h" // appease syntax parser

#include "itkImageRegionIterator.h"

template <typename TImage>
std::vector<float> PatchClustering::VectorizePatch(const TImage* const image, const itk::ImageRegion<2>& region)
{
  std::vector<float> vectorized(image->GetNumberOfComponentsPerPixel() * region.GetNumberOfPixels());
  
  itk::ImageRegionIterator<TImage> imageIterator(image, region);

  unsigned int patchRadius = 5;

  unsigned int pixelCounter = 0;
  while(!imageIterator.IsAtEnd())
    {
    for(unsigned int component = 0; component < image->GetNumberOfComponentsPerPixel(); ++component)
      {
      vectorized[component * pixelCounter] = imageIterator.Get()[component];
      }
    pixelCounter++;
    ++imageIterator;
    }
  return vectorized;
}
