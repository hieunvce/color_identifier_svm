//
// Created by hieunguyen on 6/18/18.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <dirent.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

#define BACKGROUND 33
#define RED        630
#define YELLOW     86
#define GREEN      -420

vector<Vec3b> pixelColor={Vec3b(255,255,255),Vec3b(0,0,255),
                          Vec3b(0,255,255),Vec3b(0,255,0),Vec3b(0,0,0)};

int colorDetermine(int value);

int main(int argc, char* argv[]){
    Mat image=imread("samples/2.jpg",CV_LOAD_IMAGE_COLOR);
    cvtColor(image,image,CV_BGR2Lab);
    Mat segImage(image.rows,image.cols,CV_8UC3,Scalar(255,255,255));
    for (int i=0;i<image.rows;i++)
    {
        const uchar *pixel=image.ptr<uchar>(i);
        for (int j=0;j<image.cols;j++){
            pixel++;
            int a=*pixel++-128;
            int b=*pixel++-128;
            int checkValue=a*10+b;
            int iColor=colorDetermine(checkValue);
            cout << iColor << endl;
            segImage.at<Vec3b>(i,j)=pixelColor[iColor];
        }
    }

    namedWindow("image",CV_WINDOW_AUTOSIZE);
    imshow("image",image);

    namedWindow("seg",CV_WINDOW_AUTOSIZE);
    imshow("seg",segImage);
    waitKey(0);
    return 0;
}

int colorDetermine(int value){
    int distanceToEachColor[4]={-1};//{BG,Red,Yellow,Green}
    if (value>=20 && value <=40)
        distanceToEachColor[0]=abs(value-BACKGROUND);
    if (value>=330 && value <=930)
        distanceToEachColor[1]=abs(value-RED);
    if (value>=-215 && value <=390)
        distanceToEachColor[2]=abs(value-YELLOW);
    if (value>=-720 && value <=-120)
        distanceToEachColor[3]=abs(value-GREEN);
    if (distanceToEachColor[0]==-1 && distanceToEachColor[1]==-1)
        if (distanceToEachColor[2]==-1 && distanceToEachColor[3]==-1)
            return 4;
    int minDistance=1408;
    int colorIndex=0;
    for (int i=0;i<4;i++){
        if (distanceToEachColor[i]>-1 && distanceToEachColor[i]<minDistance) {
            minDistance = distanceToEachColor[i];
            colorIndex = i;
        }
    }
    return colorIndex;
}