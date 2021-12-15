#include "compressor_decompressor.hpp"

//TODO: Write readme.
//TODO: Fix quantizer.
//TODO: Recreate w/ DCT.
//TODO: Write report.

void dftCompressor(const cv::Mat& original, cv::Mat& compressed, int subimage_dim, std::vector<std::vector<int>> matrix) {
    cv::Mat labels;
    std::vector<cv::Mat> temp;
    compressed.rows = original.rows;
    compressed.cols = original.cols;
    cv::split(original, temp);
    temp[0].convertTo(temp[0], CV_32FC1);
    temp[1].convertTo(temp[1], CV_32FC1);
    temp[2].convertTo(temp[2], CV_32FC1);
    if (((original.rows % subimage_dim) != 0) || ((original.cols % subimage_dim) != 0)) {
        throw 1;
    }
    for (int i = 0; i < (original.cols); i += subimage_dim) {
        for (int j = 0; j < (original.rows); j += subimage_dim) {
            for (int k = 0; k < 3; k++) {
                //DFT transform
                cv::dft(temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)), temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)));
                //Quantize
                for (int l = 0; l < subimage_dim; l++) {
                    for (int m = 0; m < subimage_dim; m++) {
                        if (subimage_dim == 8) {
                            temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)).at<double>(l, m) /= matrix[l][m];
                            temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)).at<double>(l, m) = temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)).at<int>(l, m);
                        }
                    }
                }
            }
        }
    }
    cv::merge(temp, compressed);
}
void dftDecompressor(const cv::Mat& compressed, cv::Mat& decompressed) {

}
std::vector<std::vector<int>> returnQuantMatrix(const int n) {
    std::vector<std::vector<int>> quantMatrix8 = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    return quantMatrix8;
}