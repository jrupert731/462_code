#include "compressor_decompressor.hpp"

//TODO: Fix decompressor
//TODO: Write readme.
//TODO: Write report.

void dftCompressor(const cv::Mat& original, cv::Mat& compressed, int subimage_dim, int coefficientsToKeep) {
    std::vector<cv::Mat> temp;
    compressed.rows = original.rows;
    compressed.cols = original.cols;
    cv::split(original, temp);
    for (int k = 0; k < temp.size(); k++) {
        temp[k].convertTo(temp[k], CV_32FC1);
    }
    if (((original.rows % subimage_dim) != 0) || ((original.cols % subimage_dim) != 0)) {
        throw 1;
    }
    for (int i = 0; i < (original.cols); i += subimage_dim) {
        for (int j = 0; j < (original.rows); j += subimage_dim) {
            for (int k = 0; k < temp.size(); k++) {
                //DFT transform
                cv::Mat temp1 = temp[k](cv::Rect(i, j, subimage_dim, subimage_dim));
                cv::dft(temp1, temp1);
                //Quantize 
                quantize(temp1, 8);         
                findLargestRemoveOthers(temp1, subimage_dim, coefficientsToKeep);
                temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)) = temp1;
            }
        }
    }
    cv::merge(temp, compressed);
    // cv::kmeans(compressed, coefficientsToKeep, labels, cv::TermCriteria(), 10, cv::KmeansFlags::KMEANS_PP_CENTERS, compressed);   
    compressed.convertTo(compressed, CV_32F);
}

void dctCompressor(const cv::Mat& original, cv::Mat& compressed, int subimage_dim, int coefficientsToKeep) {
    std::vector<cv::Mat> temp;
    cv::Mat labels;
    compressed.rows = original.rows;
    compressed.cols = original.cols;
    cv::split(original, temp);
    for (int k = 0; k < temp.size(); k++) {
        temp[k].convertTo(temp[k], CV_32FC1);
    }
    if (((original.rows % subimage_dim) != 0) || ((original.cols % subimage_dim) != 0)) {
        throw 1;
    }
    for (int i = 0; i < (original.cols); i += subimage_dim) {
        for (int j = 0; j < (original.rows); j += subimage_dim) {
            for (int k = 0; k < temp.size(); k++) {
                //DFT transform
                cv::Mat temp1 = temp[k](cv::Rect(i, j, subimage_dim, subimage_dim));
                cv::dct(temp1, temp1);
                // //Quantize
                quantize(temp1, 8);
                //cv::kmeans(temp1, coefficientsToKeep, labels, cv::TermCriteria(), 10, cv::KmeansFlags::KMEANS_PP_CENTERS, temp1);                     
                findLargestRemoveOthers(temp1, subimage_dim, coefficientsToKeep);
                temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)) = temp1;
            }
        }
    }
    cv::merge(temp, compressed);
    compressed.convertTo(compressed, CV_32F);
}

void dftDecompressor(const cv::Mat& original, cv::Mat& decompressed, int subimage_dim) {
    std::vector<cv::Mat> temp;
    decompressed.rows = original.rows;
    decompressed.cols = original.cols;
    if (((original.rows % subimage_dim) != 0) || ((original.cols % subimage_dim) != 0)) {
        throw 1;
    }
    cv::split(original, temp);
    for (int k = 0; k < temp.size(); k++) {
        temp[k].convertTo(temp[k], CV_32FC1);
    }
    for (int i = 0; i < (original.cols); i += subimage_dim) {
        for (int j = 0; j < (original.rows); j += subimage_dim) {
            for (int k = 0; k < temp.size(); k++) {
                cv::Mat temp1 = temp[k](cv::Rect(i, j, subimage_dim, subimage_dim));
                // //Quantize
                //reverseQuantize(temp1, subimage_dim);
                //DFT transform
                cv::idft(temp1, temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)), CV_HAL_DFT_SCALE);
                //temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)) = temp1;
            }
        }
    }
    cv::merge(temp, decompressed);
    decompressed.convertTo(decompressed, CV_32F);
}

void dctDecompressor(const cv::Mat& original, cv::Mat& decompressed, int subimage_dim) {
    std::vector<cv::Mat> temp;
    decompressed.rows = original.rows;
    decompressed.cols = original.cols;
    if (((original.rows % subimage_dim) != 0) || ((original.cols % subimage_dim) != 0)) {
        throw 1;
    }
    cv::split(original, temp);
    for (int k = 0; k < temp.size(); k++) {
        temp[k].convertTo(temp[k], CV_32FC1);
    }
    for (int i = 0; i < (original.cols); i += subimage_dim) {
        for (int j = 0; j < (original.rows); j += subimage_dim) {
            for (int k = 0; k < temp.size(); k++) {
                cv::Mat temp1 = temp[k](cv::Rect(i, j, subimage_dim, subimage_dim));
                // //Quantize
                //reverseQuantize(temp1, subimage_dim);
                //DCT transform
                cv::idct(temp1, temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)));
                //temp[k](cv::Rect(i, j, subimage_dim, subimage_dim)) = temp1;
            }
        }
    }
    cv::merge(temp, decompressed);
    decompressed.convertTo(decompressed, CV_32F);
}

void quantize(cv::Mat& original, int subimage_dim) {
    int quantMatrix8[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    // for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 8; j++) {
    //         quantMatrix8[i][j] /= 256.0;
    //     }
    // }
    //cv::divide(original, cv::Mat(8, 8, CV_8UC1, &quantMatrix8), original, 1.0, CV_8UC1);
    //cv::multiply(original, cv::Mat(8, 8, CV_8UC1, &quantMatrix8), original, 1.0, CV_8UC1);

    

    for (int l = 0; l < subimage_dim; l++) {
        for (int m = 0; m < subimage_dim; m++) {
            int temp = original.at<float>(l, m);
            //std::cout << temp << " " << 256 / quantMatrix8[l][m]; 
            temp /= (quantMatrix8[l][m]); // *= 256.0;
            temp *= (quantMatrix8[l][m]);
            original.at<float>(l, m) = temp;

            //std::cout << " " << temp << " " << original.at<int>(l,m) << std::endl;
        }
    }
}

void reverseQuantize(cv::Mat& original, int subimage_dim) {
    int quantMatrix8[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    // for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 8; j++) {
    //         quantMatrix8[i][j] /= 256.0;
    //     }
    // }
    //cv::multiply(original, cv::Mat(8, 8, CV_8UC1, &quantMatrix8), original, 1.0, CV_32FC1);
    for (int l = 0; l < subimage_dim; l++) {
        for (int m = 0; m < subimage_dim; m++) {
            original.at<int>(l, m) *= (256 / quantMatrix8[l][m]);// /= 256.0;
        }
    }
}



void findLargestRemoveOthers(cv::Mat& original, int dim, int numberKept) {
    std::vector<double> max;
    int used = 0;
    for (int i = 0; i < numberKept; i++) {
        max.push_back(original.at<float>(i, 0));
        used++;
    }
    for (int k = 0; k < used-1; k++) {
        if (abs(max[k]) > abs(max[k+1])) {
            max[k] = max[k+1];
            max[k+1];
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 1; j < dim; j++) {
            if (abs(max[0]) < abs(original.at<float>(i, j)))
                max[0] = original.at<float>(i, j);
            for (int k = 0; k < used-1; k++) {
                if (abs(max[k]) > abs(max[k+1])) {
                    max[k] = max[k+1];
                    max[k+1] = original.at<float>(i, j);
                }
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (abs(original.at<float>(i, j)) < max[0]) {
                original.at<float>(i, j) = 0;
            }
        }
    }
}

// int[][] returnQuantMatrix(const int n) {
//     int quantMatrix8[8][8] = {
//         {16, 11, 10, 16, 24, 40, 51, 61},
//         {12, 12, 14, 19, 26, 58, 60, 55},
//         {14, 13, 16, 24, 40, 57, 69, 56},
//         {14, 17, 22, 29, 51, 87, 80, 62},
//         {18, 22, 37, 56, 68, 109, 103, 77},
//         {24, 35, 55, 64, 81, 104, 113, 92},
//         {49, 64, 78, 87, 103, 121, 120, 101},
//         {72, 92, 95, 98, 112, 100, 103, 99}
//     };
//     return quantMatrix8;
// }