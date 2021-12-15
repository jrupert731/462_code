#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdint>
#include <vector>

void dftCompressor(const cv::Mat& original, cv::Mat& compressed, int subimage_dim, std::vector<std::vector<int>> matrix);
void dftDecompressor(const cv::Mat& compressed, cv::Mat& decompressed);
std::vector<std::vector<int>> returnQuantMatrix(const int n);