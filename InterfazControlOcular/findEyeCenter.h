#ifndef FINDEYECENTER_H
#define FINDEYECENTER_H
#include "opencv2/imgproc/imgproc.hpp"

cv::Point findEyeCenter(cv::Mat face, cv::Rect eye, std::string debugWindow);


#endif // FINDEYECENTER_H
