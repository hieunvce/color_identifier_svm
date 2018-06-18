//
// Created by hieunguyen on 6/18/18.
//
#include "svm_functions.h"

extern vector<Point> training_points;
extern vector<int> training_labels;
extern const int testStep;
extern vector<string> classes;

int main(int argc, char* argv[]){
    //-----------training----------------------------------
    /*
    // loading train data
    initClasses();
    vector<string> dirsTrain;
    for (int i=0;i<classes.size();i++){
        dirsTrain.push_back("./data/"+classes[i]+"/");
    }
    loadDataDir(dirsTrain);
    trainSVMModel(10);
    */
    //----------end training-----------------------------
    //----------testing----------------------------------
    
    //----------endtesting-------------------------------
    return 0;
}
