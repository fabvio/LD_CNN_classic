# Lane detection for Unipr Course in Computer Vision for Vehicle
Lane detection with a classical and with a deep learning based approach for Computer Vision for Vehicle course. Contains a simple lane detection algorithm and inference in C++/libtorch for a pretrained [ERFNet](https://ieeexplore.ieee.org/document/8063438) on TuSimple with [Hsu clustering loss](https://arxiv.org/abs/1803.06459).

## Tasks for Ex. 1

1) Load the KITTI odometry01 directory in greyscale and visualize it
2) Obtain a IPM image applying the homography matrix given
3) Process the IPM with a DLD kernel
4) Binarize the obtained image with a fixed threshold
5) Binarize the obtained image with an adaptive threshold: `LANE(x,y) = (DLD(x,y) > alpha*AVG(x,y)) ? 255 : 0`
6) Cluster the points together. A point belongs to a cluster if it is near (NxN) to a point in that cluster.
7) Bonus: fitting with Hough Transform
<p align="center">
  <img src="DLD.gif">
</p>
<<<<<<< Updated upstream

### Hints for the clustering algorithm
1) Start from the bottom of the binarized image and proceed
2) Use `cv::Point2d` if you want `std::vector< std::vector <cv::Point2d> >`
3) Visualize the clusters with random colors using `rand()` or color palette

### Hints for Hough Transform
2) The conversion between the cartesian and polar space is `r = cos(t) * (x) + sin(t) * (y)`
3) Pay attention to degrees and radiants!

## Tasks for Ex. 2

1) Load the CNN using `std::shared_ptr<torch::jit::script::Module> module = torch::jit::load("../res/model_cpp.cnn");`
2) Read the images in the 0531 folder in `READ_COLOR` mode
3) Resize the images (512x256) with `cv::resize(scr_im, dst_im, cv::Size(w, h));`
4) Convert the images using `tc.toTensor(image)` initializing an object `tc = TConverter();`
5) Create a`std::vector` of `torch::jit::IValue` and `push_back` the Tensor 
6) Forward the array inside the neural network with `at::Tensor output = module->forward(inputs).toTensor();`
7) Get the output with       
      ```
      std::tuple<at::Tensor, at::Tensor> output_max = at::max(output, 1);
      at::Tensor argmax = std::get<1>(output_max);
      argmax = argmax.to(at::kByte);
      ```
8) Visualize the different lanes with different colors. Get the prediction image with `cv::Mat prediction_vectors = tc.toImage(argmax, TConverter::CONVERT_GRAYSCALE, image.size());`. You will get a matrix where 0=background, 1/2/3/4 = different lanes.

<hr>

## Possible issues

1) libprotobuf not found when compiling Lane_CNN: `sudo apt-get install libprotobuf-dev`
2) Issues with `imshow`: try to manually download and compile OpenCV
3) Other issues with libtorch: manually download libtorch and link it with `cmake -DCMAKE_PREFIX_PATH=path/to/libtorch ..` 
4) Issues with libmklml: download it from the repo and place it in `libtorch/lib`
=======
>>>>>>> Stashed changes
