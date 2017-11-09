#pragma once

#include "opencv2/opencv.hpp"


using namespace cv;


void ColorReduce(const Mat& image, Mat& outImage, int div);
void InverseColor(const Mat& image, Mat& outImage);
void TranslateTransform(const Mat& image, Mat& outImage, int dx, int dy);