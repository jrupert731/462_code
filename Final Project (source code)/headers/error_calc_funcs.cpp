#include "error_calc_funcs.hpp"
/*
using namespace std;
using namespace cv;
*/
double rmsError(const cv::Mat& image_a, const cv::Mat& image_b) {
    double error_total = 0;
    cv::Mat temp1, temp2;
    image_a.convertTo(temp1, CV_32F);
    image_b.convertTo(temp2, CV_32F);
    for (uint64_t i = 0; i < temp1.cols; i++) {
        for (uint64_t j = 0; j < temp1.rows; j++) {
            error_total += pow((temp1.at<double>(cv::Point(i, j)) - temp2.at<double>(cv::Point(i, j))), 2);
        }
    }
    error_total /= ((temp1.rows)*(temp1.cols));
    error_total = sqrt(abs(error_total));
    return error_total;
}

double signalToNoiseRatio(const cv::Mat& image_a, const cv::Mat& image_b) {
    double error_total = 0;
    double signal_total = 0;
    cv::Mat temp1, temp2;
    image_a.convertTo(temp1, CV_32F);
    image_b.convertTo(temp2, CV_32F);
    for (uint64_t i = 0; i < temp1.cols; i++) {
        for (uint64_t j = 0; j < temp1.rows; j++) {
            error_total += pow((temp1.at<double>(cv::Point(i, j)) - temp2.at<double>(cv::Point(i, j))), 2);
            signal_total += temp2.at<double>(cv::Point(i, j))*temp2.at<double>(cv::Point(i, j));
        }
    }
    return signal_total / error_total;
}