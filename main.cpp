//
// Created by hieunguyen on 6/18/18.
//
#include <opencv/cv.hpp>
#include "svm_functions.h"

extern vector<Point> training_points;
extern vector<int> training_labels;
extern const int testStep;
extern vector<string> classes;
Ptr<SVM> svm;

int main(int argc, char* argv[]){
    /*//-----------training----------------------------------

    // loading train data
    initClasses();
    vector<string> dirsTrain;
    for (int i=0;i<classes.size();i++){
        dirsTrain.push_back("./data/"+classes[i]+"/");
    }
    loadDataDir(dirsTrain);
    trainSVMModel(10);

    //----------end training-----------------------------
    //----------testing----------------------------------
    cout << "Init classes..." << endl;
    initClasses();
    cout << "Read image..." << endl;
    Mat srcImg=imread("test.jpg",CV_LOAD_IMAGE_COLOR);
    Mat LabImg(srcImg.rows, srcImg.cols, CV_8UC3);
    cvtColor(srcImg, LabImg, COLOR_BGR2Lab);

    Mat segImg=srcImg.clone();

    cout << "Segmenting image..." << endl;
    segImg=segmentImage(svm,LabImg);

    namedWindow("result",CV_WINDOW_AUTOSIZE);
    imshow("result",segImg);
    waitKey(0);
    //----------endtesting-------------------------------
     */

    Mat image=imread("image.jpg",CV_LOAD_IMAGE_COLOR);
    cvtColor(image,image,CV_BGR2Lab);

    for (int i=0;i<image.rows;i++)
    {
        for (int j=0;j<image.cols;j++){
            Vec3b pixel=image.at<Vec3b>(Point(i,j));
            int a=pixel[1];
            int b=pixel[2];
            int checkValue=a*10+b;

        }
    }

    namedWindow("image",CV_WINDOW_AUTOSIZE);
    imshow("image",image);
    waitKey(0);
    return 0;
}
