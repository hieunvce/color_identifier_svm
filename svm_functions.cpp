//
// Created by hieunguyen on 6/18/18.
//


#include "svm_functions.h"

vector<Point> training_points;
vector<int> training_labels;
const int testStep = 5;
vector<string> classes;

void initClasses(){
    classes.push_back("background");
    classes.push_back("red");
    classes.push_back("yellow");
    classes.push_back("green");
    classes.push_back("other");
}

void addPointsValue(Mat image, int color){
    //Size standardSize(500,500);
    //resize(image,image,standardSize);

    Mat LabImg(image.rows, image.cols, CV_8UC3);
    cvtColor(image, LabImg, COLOR_BGR2Lab);

    for (int i=0;i<LabImg.rows;i++) {
        const uchar *lab_data = LabImg.ptr<uchar>(i);
        for (int j=0;j<LabImg.cols;j++){
            lab_data++;//skip L
            int a=*lab_data++;
            int b=*lab_data++;

            Point point;
            point.x=a;
            point.y=b;

            training_points.push_back(point);
            training_labels.push_back(color);
        }
    }
}

void loadDataDir(vector<string> dirsName){
    cout << "Loading image data..." << endl;
    for (int i=0;i<dirsName.size();i++){
        string dirName=dirsName[i];
        DIR *dp;
        struct dirent *dirp;
        if((dp  = opendir(dirName.c_str())) == NULL) {
            cout << "Error, cant find directory!" << endl;
        }
        while ((dirp=readdir(dp)) != NULL){
            string name=string(dirp->d_name);
            if(name!="."&&name!=".."){
                Mat img=imread(dirName+name);
                addPointsValue(img,i);
            }
        }
        closedir(dp);
    }
}

static Mat prepareTrainSamples(const vector<Point> &pts)
{
    Mat samples;
    Mat(pts).reshape(1, (int)pts.size()).convertTo(samples, CV_32F);
    return samples;
}

static Ptr<TrainData> prepareTrainData()
{
    Mat samples = prepareTrainSamples(training_points);
    return TrainData::create(samples, ROW_SAMPLE, Mat(training_labels));
}


void trainSVMModel(double C)
{
    cout << "Training..." << endl;
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::POLY); //SVM::LINEAR;
    svm->setDegree(0.5);
    svm->setGamma(1);
    svm->setCoef0(1);
    svm->setNu(0.5);
    svm->setP(0);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 1000, 0.01));
    svm->setC(C);
    svm->train(prepareTrainData());
    svm->save("color_classifier.yml");
}
