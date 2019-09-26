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
#define THREAD_NUM 8

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

struct param{
    int size;
    int tidx;

};


void * std_output(void *pa){
    struct param *local = (struct param *) pa;
    int size = local->size;
    int tidx = local->tidx;

    pthread_mutex_lock(&count_mutex);
    int count = 0;
    int i = tidx;
    ifstream file(filename);
    string line;
    while(i < size&&file.is_open()){
        //file.seekg(i, ios::beg);
        getline(file, line);
        count++;
        i+=THREAD_NUM;
     }
    
    cout << " thread " << tidx << " has " << count << " lines" << endl;
    pthread_mutex_unlock(&count_mutex);
    
}


int main(){

    
    mid = clock();
    //int LINE_PER_THREAD = line_num / THREAD_NUM;
    pthread_t threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        struct param *str_param = new param();
        str_param->size = 16777217; 
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
