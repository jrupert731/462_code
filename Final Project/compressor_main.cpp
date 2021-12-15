#include "headers/compressor_decompressor.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>

//Takes four arguments: Input filename, output filename, "dft" or "dct" to indicate type of transform, block size (for instance, "8" for an 8x8 block) 

int main(int argc, char *argv[]) {
    cv::Mat input = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat output = cv::Mat();
    if ((std::string)argv[3] == "dft") {
        try { dftCompressor(input, output, atoi(argv[4]), returnQuantMatrix(atoi(argv[4]))); }
        catch (int e) {
            if (e == 1) {
                std::cout << "Block size does not fit image size" << std::endl;
                return 0;
            }
        }
    } else if ((std::string)argv[3] == "dct") {

    }
    cv::imwrite(argv[2], output);
}