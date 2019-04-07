#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/types.hpp>

// Class definition
class IPMHelper{
  public:
    cv::Mat getIpm();
};

// This function returns an IPM matrix for the KITTI odometry sequence
cv::Mat IPMHelper::getIpm(){
  cv::Mat h_mat = cv::Mat::zeros(cv::Size(3, 3), CV_32FC1);
  h_mat.at<float>(0,0) = 35.9428 / 38.4047;
  h_mat.at<float>(0,1) = -30.3561 / 38.4047;
  h_mat.at<float>(0,2) = 19760.7 / 38.4047;
  
  h_mat.at<float>(1,1) = -8.71342 / 38.4047;
  h_mat.at<float>(1,2) = 7124.86 / 38.4047;
  
  h_mat.at<float>(2,1) = -0.0499942 / 38.4047;
  h_mat.at<float>(2,2) = 38.4047 / 38.4047;

  return h_mat.inv();
}
