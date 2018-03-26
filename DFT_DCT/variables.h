//
//  variables.h
//  test
//
//  Created by Vineet Gattani on 9/27/17.
//  Copyright © 2017 ASU. All rights reserved.
//

#ifndef variables_h
#define variables_h
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdint.h>
using namespace cv;
using namespace std;
int kernel_size = 3;
int scale = 1;
int delta = 0;
int ddepth = CV_16S;
Mat src_float;
Mat dft_setup;
Mat dft_dst;
const char* filename;
Mat src;
Mat dft_mag;
Mat inverseDFT;
Mat dct_reconstruction;
Mat dct_float;
const char* d;

#endif /* variables_h */
