#include <stdlib.h>
#include <stdio.h>
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

struct param{
  int tidx;
  int count;
};


void * std_output(void *pa){
    struct param *local = (struct param *) pa;
    int tidx = local->tidx;
    //local->count = 0;
    int count = 0;
    std::string filename = std::to_string(tidx)+".txt";
    fprintf(stderr, "thread %d is going to open file %s\n", tidx, filename.c_str());
    FILE * file_ptr = fopen(filename.c_str(), "r");
    char * line_str = (char *)calloc(1024, sizeof(char));
    if (NULL == line_str) {
      fprintf(stderr, "No Memory\n");
      exit(0);
    }
    while (fgets(line_str, 1024, file_ptr)) {
      //local->count++;
      count++;
    }
    fprintf(stderr, "thread %d has %d lines\n", tidx, local->count);
    free(line_str);
    fclose(file_ptr);
    local->count = count;
}


int main(){
    mid = clock();
    pthread_t threads[THREAD_NUM];
    vector<struct param *> param_vec;
    for(int i = 0; i < THREAD_NUM; i++){
        //struct param *str_param = new param();
      struct param *str_param = new param();
      str_param->tidx = i;
      param_vec.push_back(str_param);
      pthread_create(&threads[i], NULL, std_output, (void *)str_param);
    }

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(threads[i], NULL);

    end_time = clock();
    unsigned long total_count =0;
    for(int i = 0; i < param_vec.size(); ++i) {
      fprintf(stderr, "thread %d, idx: %d, count: %d\n", i, param_vec[i]->tidx, param_vec[i]->count);
      total_count += param_vec[i]->count;
    }
    cout << "total count: " << total_count << endl;
    double endtime = (double)(end_time-mid)/CLOCKS_PER_SEC;
    cout << "endtime "<<endtime<<endl;
    return 0;
}
