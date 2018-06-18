//
// Created by hieunguyen on 6/18/18.
//

#ifndef POINTS_CLASSIFIER_SVM_FUNCTIONS_H
#define POINTS_CLASSIFIER_SVM_FUNCTIONS_H

#endif //POINTS_CLASSIFIER_SVM_FUNCTIONS_H

#include <string>
#include <iostream>
#include <dirent.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/highgui.hpp"


using namespace std;
using namespace cv;
using namespace cv::ml;

enum Color{
    BACKGROUND, RED, YELLOW, GREEN, OTHER
};

void initClasses();
void addPointsValue(Mat image, int color);//Get a & b value in Lab color space of class
void loadDataDir(vector<string> dirsName);
static Mat prepareTrainSamples(const vector<Point> &pts);
static Ptr<TrainData> prepareTrainData();
void trainSVMModel(double C);
