#include "headers/error_calc_funcs.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>

//Argument format: Original filename, compressed-decompressed filename, "rms" for rmsError, or "sn" for signal to noise

int main(int argc, char* argv[]) {
    cv::Mat original = cv::imread(argv[1], CV_32F);
    cv::Mat decompressed = cv::imread(argv[2], CV_32F);
    if ((std::string)argv[3] == "rms") {
        std::cout << rmsError(original, decompressed) << std::endl;
    } else if ((std::string)argv[3] == "sn") {
        std::cout << signalToNoiseRatio(original, decompressed) << std::endl;
    }
}