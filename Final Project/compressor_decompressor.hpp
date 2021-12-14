#pragma once;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdint>

void compressor(cv::Mat& original, cv::Mat& compressed);
void decompressor(cv::Mat& compressed, cv::Mat& decompressed);