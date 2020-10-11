/*
 * File:
 * ----------------------
 */


#include <iostream>
#include <fstream>
#include "filelib.h"
using namespace std;

void averageValueInFile(string filename, double& result) {
    
    ifstream fin;
    fin.open(filename.c_str());
    double sum = 0;
    double n = 0;
    
    double val;
    while(fin >> val) {
        sum += val;
        n++;
    }
    
    result = sum / n;
    
}


int main() {
    
    while(true) {
        string filename;
        cout << "Enter filename of doubles:";
        cin >> filename;
        while(!fileExists(filename)){
            cout << "No such file. Enter filename of doubles:";
            cin >> filename;
        }
        
        double out = 0;
        averageValueInFile(filename, out);
        cout << "Average value in " << filename << ": " << out << endl;
    }
    return 0;
}

