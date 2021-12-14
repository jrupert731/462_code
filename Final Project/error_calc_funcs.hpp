#pragma once;

#include <opencv2/core.hpp>
#include <cmath>
#include <cstdint>

double rmsError(const cv::Mat& image_a, const cv::Mat& image_b);
double signalToNoiseRatio(const cv::Mat& image_a, const cv::Mat& image_b);