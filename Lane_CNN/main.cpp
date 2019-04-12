#include <iostream>
#include <torch/torch.h>
#include <torch/script.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "viz_utils.hpp"
#include "net_utils.hpp"


// Could be done also with blending but I'm lazy
// Color the image pixel according to the prediction
void color(cv::Mat& image, cv::Mat prediction_vectors){
  for(int y = 0; y < image.rows; y++){
    for(int x = 0; x < image.cols; x++){
      if(prediction_vectors.at<uchar>(y,x) == 1){
        image.at<cv::Vec3b>(y,x) = cv::Vec3b(255, 0, 0);
      }
      else if(prediction_vectors.at<uchar>(y,x) == 2){
        image.at<cv::Vec3b>(y,x) = cv::Vec3b(0, 255, 0);
      }
      else if(prediction_vectors.at<uchar>(y,x) == 3){
        image.at<cv::Vec3b>(y,x) = cv::Vec3b(0, 0, 255);
      }
      else if(prediction_vectors.at<uchar>(y,x) == 4){
        image.at<cv::Vec3b>(y,x) = cv::Vec3b(255, 255, 0);
      }
    }
  }
}

int main(int argc, char **argv) {

    // Passing the directory as a command line argument
    std::string folder = argv[1];

    // Initializing the required components
    DirLoader dl = DirLoader(folder, DirLoader::READ_COLOR);
    TConverter tc = TConverter();
    cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("prediction", CV_WINDOW_AUTOSIZE);
    
    // Stage one: Loading model + loading weights
    std::shared_ptr<torch::jit::script::Module> module = torch::jit::load("../res/model_cpp.cnn");
    
    // Iterate over images
    for(int i = 0; i < dl.getNumImages(); i++){
      cv::Mat image;

      // Pytorch requires to submit to the network a vector of inputs of this type. Only framework stuff
      std::vector<torch::jit::IValue> inputs;
    
      // The network is trained with 512x256 images, better use this size
      cv::resize(dl.getNextImage(), image, cv::Size(512, 256));
      cv::imshow("image", image);

      // Convert to Tensor using the helper class
      // Saves everything in a tensor, swaps some dimensions because opencv saves images in WxHxC format, we need CxHxW.
      // Again, framework stuff. Finally, it divides everything by 255 to get a 0-1 float32 matrix.
      at::Tensor image_tensor = tc.toTensor(image); 
      
      // Push back the input image
      inputs.push_back(image_tensor);

      // Inference phase
      at::Tensor output = module->forward(inputs).toTensor();

      // Extracting the prediction: we have a quantity that is directly proportional to probability.
      // To extract the most probable class, we take the argmax of that quantity.
      std::tuple<at::Tensor, at::Tensor> output_max = at::max(output, 1);
      at::Tensor argmax = std::get<1>(output_max);
      argmax = argmax.to(at::kByte);

      // Ouptut
      cv::Mat prediction_vectors = tc.toImage(argmax, TConverter::CONVERT_GRAYSCALE, image.size());
      color(image, prediction_vectors);
      cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
      cv::imshow("prediction", image);
      
      
      cv::waitKey(0);
    }
    return 0;
  
}
