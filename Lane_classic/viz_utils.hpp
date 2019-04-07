#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*!
* \brief This class loads all the images in a directory
*/
class DirLoader{

  public:
    enum read_modes{
      READ_GRAYSCALE,
      READ_COLOR
    };

    DirLoader(std::string dir_path, read_modes mode);
    cv::Mat getNextImage();
    cv::Mat getPreviousImage();
    int getNumImages();

    private:
    std::string dir_path;
    int index;
    std::vector<std::string> images_paths;
    read_modes mode;
    void readImage(cv::Mat& image);

};

/*! Class constructor.
* \param dir_path the directory where the images are stored
* \param mode color or greyscale
*/
DirLoader::DirLoader(std::string dir_path, DirLoader::read_modes mode)
{
  this->dir_path = dir_path;
  this->index = -1;
  this->mode = mode;

  DIR *dp;
  struct dirent *dirp;

  if((dp  = opendir(dir_path.c_str())) == NULL) {
      std::cout << "Error(" << errno << ") opening " << dir_path << std::endl;
  }

  while ((dirp = readdir(dp)) != NULL) {
      if(std::string(dirp->d_name) != ".." && std::string(dirp->d_name) != "."){
	this->images_paths.push_back(this->dir_path + "/" + std::string(dirp->d_name));
      }
  }
  std::sort(this->images_paths.begin(), this->images_paths.end());
  std::cout << "Found " << this->images_paths.size() << std::endl;

  closedir(dp);

}

/*! Loads the next image.
*/
cv::Mat DirLoader::getNextImage()
{

  this->index++;
  if(this->index >= this->images_paths.size()){
    this->index = 0;
    std::cout << "Looping" << std::endl;
  }
  cv::Mat image;

  this->readImage(image);

  return image;

}

/*! Loads an image pointed by index
*/
void DirLoader::readImage(cv::Mat& image)
{

  std::string path = this->images_paths[this->index];
  std::cout << path << std::endl;

  if(this->mode == DirLoader::READ_GRAYSCALE){
    image = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
  }
  else if (this->mode == DirLoader::READ_COLOR){
    image = cv::imread(path, CV_LOAD_IMAGE_COLOR);
  }

}

/*! Loads the previous image.
*/
cv::Mat DirLoader::getPreviousImage()
{
  this->index--;
  if(this->index < 0){
    this->index = this->images_paths.size() - 1;
    std::cout << "Looping" << std::endl;
  }

  cv::Mat image;

  this->readImage(image);

  return image;


}

/*! Returns the number of images in the directory
*/
int DirLoader::getNumImages()
{
  return this->images_paths.size();
}
