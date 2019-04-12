#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <torch/torch.h>

class TConverter{
public:
  enum mode_convert{
    CONVERT_COLOR,
    CONVERT_GRAYSCALE
  };
  TConverter();
  at::Tensor toTensor(cv::Mat image);
  cv::Mat toImage(torch::Tensor& tensor, TConverter::mode_convert, cv::Size sizes);
};

TConverter::TConverter(){}

/*! Converts an image to a tensor
* It is supposed that the image is in format D1xD2xC
* The output tensor will be BxCxD1xD2 
*/
at::Tensor TConverter::toTensor(cv::Mat image)
{
  cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
  at::Tensor tensor_image = torch::from_blob(image.data, {image.rows, image.cols, 3}, at::kByte); 
  tensor_image = tensor_image.unsqueeze(0);
  tensor_image = tensor_image.permute({0, 3, 1, 2});
  tensor_image = tensor_image.to(at::kFloat);
  tensor_image /= 255;
  
  return tensor_image;
}

/*! Converts a tensor to an image
* Addtitional control is given over the number of channels. It requires to know the resulting image size.
*/

cv::Mat TConverter::toImage(at::Tensor& tensor, TConverter::mode_convert mode, cv::Size sizes)
{
  cv::Mat image;
  if(mode == TConverter::CONVERT_COLOR){
    image = cv::Mat(sizes, CV_8UC3, tensor.data_ptr()); 
  }
  else if(mode == TConverter::CONVERT_GRAYSCALE){
    image = cv::Mat(sizes, CV_8UC1, tensor.data_ptr()); 
  }
  return image;
}




<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
