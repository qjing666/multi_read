#include <sstream>
#include <pthread.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

clock_t mid,end_time;
#define THREAD_NUM 64

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

struct param{
    int tidx;

};


void * std_output(void *pa){
    struct param *local = (struct param *) pa;
    int tidx = local->tidx;

    int count = 0;
    std::string filename = std::to_string(tidx)+".txt";
    cout << filename <<endl;
    ifstream file(filename);
    string line;
    while(!file.eof()&&file.is_open()){
        getline(file,line);
        count++;
    }
    
    cout << " thread " << tidx << " has " << count << " lines" << endl;
    
}


int main(){

    mid = clock();
    pthread_t threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        struct param *str_param = new param();
        str_param->tidx = i;
        pthread_create(&threads[i], NULL, std_output, (void *) str_param);
    }

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(threads[i], NULL);
    
    end_time = clock();
    double endtime = (double)(end_time-mid)/CLOCKS_PER_SEC;
    cout << "endtime "<<endtime<<endl;
    return 0;
}
