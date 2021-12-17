#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int argc, char* argv[]) {
    cv::Mat input = cv::imread(argv[1]);
    cv::Mat output; 
    input.convertTo(output, CV_32F);
    cv::patchNaNs(output, 0);
    cv::imwrite(argv[1], output);
}