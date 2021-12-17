#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdint>
#include <vector>
#include <iostream>

void dftCompressor(const cv::Mat& original, cv::Mat& compressed, int subimage_dim, int coefficientsToKeep);
void dftDecompressor(const cv::Mat& compressed, cv::Mat& decompressed, int subimage_dim);
void dctCompressor(const cv::Mat& original, cv::Mat& compressed, int subimage_dim, int coefficientsToKeep);
void dctDecompressor(const cv::Mat& compressed, cv::Mat& decompressed, int subimage_dim);
void findLargestRemoveOthers(cv::Mat& original, int dim, int numberKept);
void quantize(cv::Mat& original, int subimage_dim);
void reverseQuantize(cv::Mat& original, int subimage_dim);
std::vector<std::vector<int>> returnQuantMatrix(const int n);