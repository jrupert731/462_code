#include "error_calc_funcs.hpp"
/*
using namespace std;
using namespace cv;
*/
double rmsError(const cv::Mat& image_a, const cv::Mat& image_b) {
    double error_total = 0;
    for (uint64_t i = 0; i < image_a.cols; i++) {
        for (uint64_t j = 0; j < image_a.rows; j++) {
            error_total += pow((image_a.at<double>(cv::Point(i, j)) - image_b.at<double>(cv::Point(i, j))), 2);
        }
    }
    error_total /= ((image_a.rows)*(image_a.cols));
    error_total = sqrt(error_total);
    return error_total;
}

double signalToNoiseRatio(const cv::Mat& image_a, const cv::Mat& image_b) {
    double error_total = 0;
    double signal_total = 0;
    for (uint64_t i = 0; i < image_a.cols; i++) {
        for (uint64_t j = 0; j < image_a.rows; j++) {
            error_total += pow((image_a.at<double>(cv::Point(i, j)) - image_b.at<double>(cv::Point(i, j))), 2);
            signal_total += image_b.at<double>(cv::Point(i, j))*image_b.at<double>(cv::Point(i, j));
        }
    }
    return signal_total / error_total;
}