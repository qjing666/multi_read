#include <sstream>
#include <pthread.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

clock_t start,open,end_time;


int main(){

    start = clock();
    //ifstream input_data("file.txt");
    ifstream input_data("test_file.txt");
    open = clock();
    double opentime = (double)(open-start)/CLOCKS_PER_SEC;
    cout<<"open time:" <<opentime <<endl;
    int line_num = 0;
    string line;
    while(input_data.is_open()){
        if(!input_data.eof()){
            getline(input_data, line);
            line_num++;
        }
        else{
            cout << "total lines:  "<< line_num << endl;
            break;
        }
    }
    input_data.close();
    end_time = clock(); 
    double endtime = (double)(end_time-start)/CLOCKS_PER_SEC;
    cout<< "endtime: "<< endtime<<endl;


    return 0;
}


