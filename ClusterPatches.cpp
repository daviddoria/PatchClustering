// STL
#include <iostream>

// ITK
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkPasteImageFilter.h"
#include "itkCovariantVector.h"

#include "ITKHelpers/ITKHelpers.h"

#include "PatchClustering.h"

typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> ImageType;
typedef itk::Image<float, 2> FloatImageType;

int main(int argc, char*argv[])
{
  std::string inputFileName = argv[1];

  std::cout << "inputFileName: " << inputFileName << std::endl;

  typedef itk::ImageFileReader<ImageType> ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFileName);
  reader->Update();

  itk::ImageRegionIterator<ImageType> imageIterator(reader->GetOutput(),
                                                      reader->GetOutput()->GetLargestPossibleRegion());

  unsigned int patchRadius = 5;

  while(!imageIterator.IsAtEnd())
    {
    itk::ImageRegion<2> region = ITKHelpers::GetRegionInRadiusAroundPixel(imageIterator.GetIndex(), patchRadius);

    if(region.IsInside(reader->GetOutput()->GetLargestPossibleRegion()))
      {

      }
    ++imageIterator;
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
